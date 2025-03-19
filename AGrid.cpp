#include "AGrid.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/KismetSystemLibrary.h" // Per il debug

AGrid::AGrid() {
    PrimaryActorTick.bCanEverTick = true;
    GridSizeX = 25;
    GridSizeY = 25;
    CellSize = 100.f;
    CellBlueprintClass = nullptr; // Assicurati di impostare questa variabile nell'editor di Unreal
}

void AGrid::BeginPlay() {
    Super::BeginPlay();
    GenerateGrid();
}

void AGrid::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void AGrid::GenerateGrid() {
    if (!CellBlueprintClass) {
        UE_LOG(LogTemp, Error, TEXT("CellBlueprintClass non è stato impostato!"));
        return;
    }

    GridCells.SetNum(GridSizeX);
    GridActors.SetNum(GridSizeX);

    for (int32 X = 0; X < GridSizeX; X++) {
        GridCells[X].SetNum(GridSizeY);
        GridActors[X].SetNum(GridSizeY);

        for (int32 Y = 0; Y < GridSizeY; Y++) {
            GridCells[X][Y] = FCell{ X, Y };

            // Aggiungi ostacoli in modo casuale (es. 20% di probabilità)
            if (FMath::RandRange(0, 100) < 20) {
                GridCells[X][Y].bIsObstacle = true;
            }

            // Crea un oggetto per la cella
            FVector WorldLocation = GetCellWorldPosition(FCell{ X, Y });
            FActorSpawnParameters SpawnParams;
            AActor* CellActor = GetWorld()->SpawnActor<AActor>(CellBlueprintClass, WorldLocation, FRotator::ZeroRotator, SpawnParams);

            if (!CellActor) {
                UE_LOG(LogTemp, Error, TEXT("Impossibile generare l'attore per la cella (%d, %d)"), X, Y);
                continue;
            }

            GridActors[X][Y] = CellActor;

            // Applica un materiale dinamico per evidenziare gli ostacoli
            if (GridCells[X][Y].bIsObstacle) {
                UStaticMeshComponent* MeshComponent = CellActor->FindComponentByClass<UStaticMeshComponent>();
                if (MeshComponent) {
                    UMaterialInstanceDynamic* DynamicMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamic(0);
                    if (DynamicMaterial) {
                        DynamicMaterial->SetVectorParameterValue("BaseColor", FLinearColor::Red);
                    }
                }
            }
        }
    }
}

AActor* AGrid::GetCellActor(FCell Cell) const {
    if (GridActors.IsValidIndex(Cell.X) && GridActors[Cell.X].IsValidIndex(Cell.Y)) {
        return GridActors[Cell.X][Cell.Y];
    }
    return nullptr;
}

TArray<FCell> AGrid::FindPath(FCell Start, FCell Goal) {
    TArray<FCell> Path;
    if (!IsValidCell(Start) || !IsValidCell(Goal)) {
        UE_LOG(LogTemp, Warning, TEXT("Cella di partenza o di arrivo non valida!"));
        return Path;
    }

    TArray<FCell> OpenSet;
    TArray<FCell> ClosedSet;
    TMap<FCell, FCell> ParentMap; // Memorizza i genitori

    OpenSet.Add(Start);

    while (OpenSet.Num() > 0) {
        FCell Current = OpenSet[0];
        for (FCell Cell : OpenSet) {
            if (Cell.GetFCost() < Current.GetFCost() || (Cell.GetFCost() == Current.GetFCost() && Cell.HCost < Current.HCost)) {
                Current = Cell;
            }
        }

        if (Current == Goal) {
            while (ParentMap.Contains(Current)) {
                Path.Add(Current);
                Current = ParentMap[Current];
            }
            Algo::Reverse(Path);
            return Path;
        }

        OpenSet.Remove(Current);
        ClosedSet.Add(Current);

        for (FCell Neighbor : GetNeighbors(Current)) {
            if (ClosedSet.Contains(Neighbor) || IsBlocked(Neighbor)) continue;

            int32 TentativeGCost = Current.GCost + GetDistance(Current, Neighbor);
            if (!OpenSet.Contains(Neighbor) || TentativeGCost < Neighbor.GCost) {
                ParentMap.Add(Neighbor, Current); // Memorizza il genitore
                Neighbor.GCost = TentativeGCost;
                Neighbor.HCost = GetDistance(Neighbor, Goal);

                if (!OpenSet.Contains(Neighbor)) {
                    OpenSet.Add(Neighbor);
                }
            }
        }
    }

    return Path;
}

bool AGrid::IsGridFullyReachable() const {
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

TArray<FCell> AGrid::GetNeighbors(FCell Cell) const {
    TArray<FCell> Neighbors;
    int32 X = Cell.X;
    int32 Y = Cell.Y;

    if (X > 0) Neighbors.Add(GridCells[X - 1][Y]);
    if (X < GridSizeX - 1) Neighbors.Add(GridCells[X + 1][Y]);
    if (Y > 0) Neighbors.Add(GridCells[X][Y - 1]);
    if (Y < GridSizeY - 1) Neighbors.Add(GridCells[X][Y + 1]);

    return Neighbors;
}

int32 AGrid::GetDistance(FCell A, FCell B) const {
    return FMath::Abs(A.X - B.X) + FMath::Abs(A.Y - B.Y);
}

void AGrid::HighlightCell(FCell Cell, FColor Color) {
    AActor* CellActor = GetCellActor(Cell);
    if (!CellActor) return;

    UStaticMeshComponent* MeshComponent = CellActor->FindComponentByClass<UStaticMeshComponent>();
    if (!MeshComponent) return;

    UMaterialInstanceDynamic* DynamicMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamic(0);
    if (DynamicMaterial) {
        DynamicMaterial->SetVectorParameterValue("BaseColor", FLinearColor(Color));
    }
}

FVector AGrid::GetCellWorldPosition(FCell Cell) const {
    return FVector(Cell.X * CellSize, Cell.Y * CellSize, 0);
}

bool AGrid::IsBlocked(FCell Cell) const {
    if (!IsValidCell(Cell)) return true;
    return GridCells[Cell.X][Cell.Y].bIsObstacle;
}

bool AGrid::IsValidCell(FCell Cell) const {
    return Cell.X >= 0 && Cell.X < GridSizeX && Cell.Y >= 0 && Cell.Y < GridSizeY;
}

TArray<FCell> AGrid::GetReachableCells(FCell StartCell, int32 Range) const {
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