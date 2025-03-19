#include "APlayerController.h"
#include "AGrid.h"
#include "AUnit.h"

AAPlayerController::AAPlayerController() {
    PrimaryActorTick.bCanEverTick = true;
}

void AAPlayerController::BeginPlay() {
    Super::BeginPlay();
    Grid = Cast<AAGrid>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AAPlayerController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void AAPlayerController::HighlightMovementRange(AAUnit* SelectedUnit) {
    if (!SelectedUnit || !Grid) return;

    TArray<FCell> ReachableCells = Grid->GetReachableCells(SelectedUnit->GetCurrentCell(), SelectedUnit->GetMovementRange());
    for (FCell Cell : ReachableCells) {
        Grid->HighlightCell(Cell, FColor::Green);
    }
}