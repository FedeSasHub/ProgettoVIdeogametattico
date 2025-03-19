#include "AGrid.h"
#include "Engine/World.h"

AAGrid::AAGrid() {
    PrimaryActorTick.bCanEverTick = true;
    GridSizeX = 25;
    GridSizeY = 25;
    CellSize = 100.f;
}

void AAGrid::BeginPlay() {
    Super::BeginPlay();
    GenerateGrid();
}

void AAGrid::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void AAGrid::GenerateGrid() {
    GridCells.SetNum(GridSizeX);
    for (int32 X = 0; X < GridSizeX; X++) {
        GridCells[X].SetNum(GridSizeY);
        for (int32 Y = 0; Y < GridSizeY; Y++) {
            GridCells[X][Y] = FCell{ X, Y };
        }
    }
}

TArray<FCell> AAGrid::FindPath(FCell Start, FCell Goal) {
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

        if (Current.X == Goal.X && Current.Y == Goal.Y) {
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

bool AAGrid::IsGridFullyReachable() {
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

TArray<FCell> AAGrid::GetNeighbors(FCell Cell) {
    TArray<FCell> Neighbors;
    int32 X = Cell.X;
    int32 Y = Cell.Y;

    if (X > 0) Neighbors.Add(GridCells[X - 1][Y]);
    if (X < GridSizeX - 1) Neighbors.Add(GridCells[X + 1][Y]);
    if (Y > 0) Neighbors.Add(GridCells[X][Y - 1]);
    if (Y < GridSizeY - 1) Neighbors.Add(GridCells[X][Y + 1]);

    return Neighbors;
}

int32 AAGrid::GetDistance(FCell A, FCell B) {
    return FMath::Abs(A.X - B.X) + FMath::Abs(A.Y - B.Y);
}

void AAGrid::HighlightCell(FCell Cell, FColor Color) {
    // Implementa l'evidenziazione della cella (es. cambiare colore del materiale)
}

FVector AAGrid::GetCellWorldPosition(FCell Cell) {
    return FVector(Cell.X * CellSize, Cell.Y * CellSize, 0);
}

bool AAGrid::IsBlocked(FCell Cell) {
    // Implementa la logica per verificare se una cella è bloccata
    return false;
}