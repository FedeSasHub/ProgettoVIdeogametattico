#include "AGrid.h"
#include "AObstacle.h"
#include "AUnitManager.h"
#include "DrawDebugHelpers.h"

AGrid::AGrid()
{
    PrimaryActorTick.bCanEverTick = false;
    GridSize = 25; // Griglia 25x25
    CellSize = 200.f; // Dimensione di ogni cella
    ObstacleCount = 0;
}

void AGrid::BeginPlay()
{
    Super::BeginPlay();

    // Inizializza la griglia e gli ostacoli
    GenerateGrid();
    GenerateObstacles(10.f); // 10% di ostacoli
    DrawGrid();

    // Crea il UnitManager
    UnitManager = GetWorld()->SpawnActor<AUnitManager>();
    if (!UnitManager)
    {
        UE_LOG(LogTemp, Error, TEXT("UnitManager non creato!"));
    }
}

void AGrid::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AGrid::GenerateGrid()
{
    // Inizializza la griglia e la matrice degli ostacoli
    GridArray.Empty();
    ObstacleGrid.Empty();

    for (int32 x = 0; x < GridSize; x++)
    {
        TArray<FVector> Column;
        TArray<bool> ObstacleColumn;
        for (int32 y = 0; y < GridSize; y++)
        {
            FVector CellPosition = FVector(x * CellSize, y * CellSize, 0);
            Column.Add(CellPosition);
            ObstacleColumn.Add(false); // Inizialmente nessun ostacolo
        }
        GridArray.Add(Column);
        ObstacleGrid.Add(ObstacleColumn);
    }
}

void AGrid::GenerateObstacles(float ObstaclePercentage)
{
    int32 TotalCells = GridSize * GridSize;
    ObstacleCount = FMath::RoundToInt(TotalCells * ObstaclePercentage / 100.0f);

    int32 Attempts = 0;
    while (Attempts < 100) // Limite di tentativi per evitare loop infiniti
    {
        // Resetta la griglia degli ostacoli
        for (int32 x = 0; x < GridSize; x++)
        {
            for (int32 y = 0; y < GridSize; y++)
            {
                ObstacleGrid[x][y] = false;
            }
        }

        // Genera ostacoli
        for (int32 i = 0; i < ObstacleCount; i++)
        {
            int32 x = FMath::RandRange(0, GridSize - 1);
            int32 y = FMath::RandRange(0, GridSize - 1);

            if (!ObstacleGrid[x][y])
            {
                ObstacleGrid[x][y] = true; // Segna la cella come ostacolo
                FVector ObstaclePosition = GetCellPosition(x, y);
                if (ObstacleClass)
                {
                    GetWorld()->SpawnActor<AObstacle>(ObstacleClass, ObstaclePosition, FRotator::ZeroRotator);
                }
            }
        }

        // Verifica la raggiungibilità
        if (IsGridFullyReachable())
        {
            break;
        }

        Attempts++;
    }

    if (Attempts >= 100)
    {
        UE_LOG(LogTemp, Error, TEXT("Impossibile generare una griglia raggiungibile!"));
    }
}

bool AGrid::IsGridFullyReachable() const
{
    // Crea una copia della griglia per marcare le celle visitate
    TArray<TArray<bool>> Visited;
    Visited.Init(TArray<bool>(), GridSize);
    for (int32 x = 0; x < GridSize; x++)
    {
        Visited[x].Init(false, GridSize);
    }

    // Usa una coda per il Flood Fill
    TQueue<TPair<int32, int32>> Queue;
    Queue.Enqueue(TPair<int32, int32>(0, 0)); // Parti dalla cella (0, 0)
    Visited[0][0] = true;

    int32 ReachableCells = 1;

    // Esegui il Flood Fill
    while (!Queue.IsEmpty())
    {
        TPair<int32, int32> CurrentCell;
        Queue.Dequeue(CurrentCell);

        // Controlla le celle adiacenti
        TArray<TPair<int32, int32>> Neighbors = {
            {CurrentCell.Key - 1, CurrentCell.Value}, // Sinistra
            {CurrentCell.Key + 1, CurrentCell.Value}, // Destra
            {CurrentCell.Key, CurrentCell.Value - 1}, // Sopra
            {CurrentCell.Key, CurrentCell.Value + 1}  // Sotto
        };

        for (const auto& Neighbor : Neighbors)
        {
            int32 X = Neighbor.Key;
            int32 Y = Neighbor.Value;

            if (IsCellValid(X, Y) && !Visited[X][Y] && !IsCellObstacle(X, Y))
            {
                Visited[X][Y] = true;
                Queue.Enqueue(TPair<int32, int32>(X, Y));
                ReachableCells++;
            }
        }
    }

    // Verifica se tutte le celle sono raggiungibili
    return ReachableCells == (GridSize * GridSize - ObstacleCount);
}

void AGrid::DrawGrid()
{
    for (int32 x = 0; x < GridSize; x++)
    {
        for (int32 y = 0; y < GridSize; y++)
        {
            FVector Start = GridArray[x][y];
            FVector EndX = FVector((x + 1) * CellSize, y * CellSize, 0);
            FVector EndY = FVector(x * CellSize, (y + 1) * CellSize, 0);

            // Disegna le linee della griglia
            DrawDebugLine(GetWorld(), Start, EndX, FColor::White, true, -1, 0, 2);
            DrawDebugLine(GetWorld(), Start, EndY, FColor::White, true, -1, 0, 2);
        }
    }
}

FVector AGrid::GetCellPosition(int32 X, int32 Y) const
{
    if (IsCellValid(X, Y))
    {
        return GridArray[X][Y];
    }
    return FVector::ZeroVector;
}

bool AGrid::IsCellValid(int32 X, int32 Y) const
{
    return X >= 0 && X < GridSize && Y >= 0 && Y < GridSize;
}

bool AGrid::IsCellObstacle(int32 X, int32 Y) const
{
    if (IsCellValid(X, Y))
    {
        return ObstacleGrid[X][Y];
    }
    return false;
}

bool AGrid::IsCellOccupied(int32 X, int32 Y) const
{
    if (!UnitManager)
    {
        UE_LOG(LogTemp, Error, TEXT("UnitManager non inizializzato!"));
        return false;
    }

    // Verifica se c'è un'unità nella cella (X, Y)
    return UnitManager->GetUnitAtPosition(X, Y) != nullptr; // Usa GetUnitAtPosition
}