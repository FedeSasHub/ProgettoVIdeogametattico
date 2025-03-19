#include "ATatticoPlayerController.h"
#include "AGrid.h"
#include "AUnit.h"

ATatticoPlayerController::ATatticoPlayerController() {
    PrimaryActorTick.bCanEverTick = true;
}

void ATatticoPlayerController::BeginPlay() {
    Super::BeginPlay();
    Grid = Cast<AGrid>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATatticoPlayerController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void ATatticoPlayerController::HighlightMovementRange(AAUnit* SelectedUnit) {
    if (!SelectedUnit || !Grid) return;

    TArray<FCell> ReachableCells = Grid->GetReachableCells(SelectedUnit->GetCurrentCell(), SelectedUnit->GetMovementRange());
    for (FCell Cell : ReachableCells) {
        Grid->HighlightCell(Cell, FColor::Green);
    }
}