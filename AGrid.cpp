#include "AGrid.h"
#include "Engine/World.h"

AGrid::AGrid() {
    PrimaryActorTick.bCanEverTick = true;
    GridSizeX = 25;
    GridSizeY = 25;
    CellSize = 100.f;
}

void AGrid::BeginPlay() {
    Super::BeginPlay();
    GenerateGrid();
}

void AGrid::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void AGrid::GenerateGrid() {
    GridCells.SetNum(GridSizeX);
    GridActors.SetNum(GridSizeX);
    for (int32 X = 0; X < GridSizeX; X++) {
        GridCells[X].SetNum(GridSizeY);
        GridActors[X].SetNum(GridSizeY);
        for (int32 Y = 0; Y < GridSizeY; Y++) {
            GridCells[X][Y] = FCell{ X, Y };
            // Crea o trova l'oggetto della cella e memorizzalo in GridActors[X][Y]
        }
    }
}
AActor* AGrid::GetCellActor(FCell Cell) {
    if (Cell.X < 0 || Cell.X >= GridSizeX || Cell.Y < 0 || Cell.Y >= GridSizeY) return nullptr;
    if (GridActors.IsValidIndex(Cell.X) && GridActors[Cell.X].IsValidIndex(Cell.Y)) {
        return GridActors[Cell.X][Cell.Y];
    }
    return nullptr;
}
TArray<FCell> AGrid::FindPath(FCell Start, FCell Goal) {
    TArray<FCell> OpenSet;
    TArray<FCell> ClosedSet;
    OpenSet.Add(Start);

    while (OpenSet.Num() > 0) {
        FCell Current = OpenSet[0];
        for (FCell Cell : OpenSet) {
            if (Cell.GetFCost() < Current.GetFCost() || (Cell.GetFCost() == Current.GetFCost() && Cell.HCost < Current.HCost)) {
                Current = Cell;
            }
        }

        if (Current == Goal) {
            TArray<FCell> Path;
            while (Current.Parent != nullptr) {
                Path.Add(Current);
                Current = *Current.Parent;
            }
            Algo::Reverse(Path);
            return Path;
        }

        OpenSet.Remove(Current);
        ClosedSet.Add(Current);

        for (FCell Neighbor : GetNeighbors(Current)) {
            if (ClosedSet.Contains(Neighbor)) continue;

            int32 TentativeGCost = Current.GCost + GetDistance(Current, Neighbor);
            if (!OpenSet.Contains(Neighbor) || TentativeGCost < Neighbor.GCost) {
                Neighbor.Parent = new FCell(Current);
                Neighbor.GCost = TentativeGCost;
                Neighbor.HCost = GetDistance(Neighbor, Goal);

                if (!OpenSet.Contains(Neighbor)) {
                    OpenSet.Add(Neighbor);
                }
            }
        }
    }

    return TArray<FCell>();
}

bool AGrid::IsGridFullyReachable() {
    TArray<FCell> VisitedCells;
    TArray<FCell> Queue;
    Queue.Add(GridCells[0][0]);

    while (Queue.Num() > 0) {
        FCell Current = Queue.Pop();
        VisitedCells.Add(Current);

        for (FCell Neighbor : GetNeighbors(Current)) {
            if (!VisitedCells.Contains(Neighbor) && !IsBlocked(Neighbor)) {
                Queue.Add(Neighbor);
            }
        }
    }

    return VisitedCells.Num() == (GridSizeX * GridSizeY);
}

TArray<FCell> AGrid::GetNeighbors(FCell Cell) {
    TArray<FCell> Neighbors;
    int32 X = Cell.X;
    int32 Y = Cell.Y;

    if (X > 0) Neighbors.Add(GridCells[X - 1][Y]);
    if (X < GridSizeX - 1) Neighbors.Add(GridCells[X + 1][Y]);
    if (Y > 0) Neighbors.Add(GridCells[X][Y - 1]);
    if (Y < GridSizeY - 1) Neighbors.Add(GridCells[X][Y + 1]);

    return Neighbors;
}

int32 AGrid::GetDistance(FCell A, FCell B) {
    return FMath::Abs(A.X - B.X) + FMath::Abs(A.Y - B.Y);
}

void AGrid::HighlightCell(FCell Cell, FColor Color) {
    // Verifica che la cella sia valida
    if (Cell.X < 0 || Cell.X >= GridSizeX || Cell.Y < 0 || Cell.Y >= GridSizeY) return;

    // Ottieni l'oggetto della cella (es. un StaticMeshActor)
    AActor* CellActor = GetCellActor(Cell);
    if (!CellActor) return;

    // Ottieni il componente di mesh della cella
    UStaticMeshComponent* MeshComponent = CellActor->FindComponentByClass<UStaticMeshComponent>();
    if (!MeshComponent) return;

    // Crea un materiale dinamico
    UMaterialInstanceDynamic* DynamicMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamic(0);
    if (DynamicMaterial) {
        // Imposta il colore del materiale
        DynamicMaterial->SetVectorParameterValue("BaseColor", FLinearColor(Color));
    }
}

FVector AGrid::GetCellWorldPosition(FCell Cell) {
    return FVector(Cell.X * CellSize, Cell.Y * CellSize, 0);
}

bool AGrid::IsBlocked(FCell Cell) {
    // Verifica che la cella sia valida
    if (Cell.X < 0 || Cell.X >= GridSizeX || Cell.Y < 0 || Cell.Y >= GridSizeY) return true;

    // Ottieni l'oggetto della cella (es. un StaticMeshActor)
    AActor* CellActor = GetCellActor(Cell);
    if (!CellActor) return false;

    // Verifica se la cella contiene un ostacolo
    // (es. controlla se l'oggetto ha un tag "Obstacle")
    if (CellActor->ActorHasTag("Obstacle")) {
        return true;
    }

    // Verifica se la cella contiene un'unità
    // (es. controlla se l'oggetto ha un tag "Unit")
    if (CellActor->ActorHasTag("Unit")) {
        return true;
    }

    return false;
}

TArray<FCell> AGrid::GetReachableCells(FCell StartCell, int32 Range) {
    TArray<FCell> ReachableCells;
    TArray<FCell> OpenSet;
    TArray<FCell> ClosedSet;

    OpenSet.Add(StartCell);

    while (OpenSet.Num() > 0) {
        FCell Current = OpenSet[0];
        OpenSet.Remove(Current);
        ClosedSet.Add(Current);

        for (FCell Neighbor : GetNeighbors(Current)) {
            if (ClosedSet.Contains(Neighbor) || IsBlocked(Neighbor)) continue;

            int32 Distance = GetDistance(StartCell, Neighbor);
            if (Distance <= Range) {
                ReachableCells.Add(Neighbor);
                OpenSet.Add(Neighbor);
            }
        }
    }

    return ReachableCells;
}