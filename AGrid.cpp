#include "AGrid.h"
#include "AObstacle.h"
#include "AUnitManager.h"
#include "DrawDebugHelpers.h"

AGrid::AGrid()
{
    PrimaryActorTick.bCanEverTick = false;
    GridSize = 25; // Griglia 25x25
    CellSize = 200.f; // Dimensione di ogni cella
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
    int32 ObstacleCount = FMath::RoundToInt(TotalCells * ObstaclePercentage / 100.0f);

    for (int32 i = 0; i < ObstacleCount; i++)
    {
        int32 x = FMath::RandRange(0, GridSize - 1);
        int32 y = FMath::RandRange(0, GridSize - 1);

        // Verifica che la cella non sia già un ostacolo
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