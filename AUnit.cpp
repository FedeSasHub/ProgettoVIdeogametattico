#include "AUnit.h"
#include "AGrid.h"

AAUnit::AAUnit() {
    PrimaryActorTick.bCanEverTick = true;
    MovementRange = 3; // Esempio per Sniper
}

void AAUnit::BeginPlay() {
    Super::BeginPlay();
}

void AAUnit::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void AAUnit::MoveToCell(FCell Destination) {
    if (!Grid) return;

    TArray<FCell> Path = Grid->FindPath(CurrentCell, Destination);
    if (Path.Num() > 0) {
        for (FCell Cell : Path) {
            SetActorLocation(Grid->GetCellWorldPosition(Cell));
            CurrentCell = Cell;
        }
    }
}