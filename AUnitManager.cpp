#include "AUnitManager.h"
#include "AUnit.h"

AUnitManager::AUnitManager() {
    PrimaryActorTick.bCanEverTick = true;
}

void AUnitManager::BeginPlay() {
    Super::BeginPlay();
}

void AUnitManager::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void AUnitManager::AddUnit(AUnit* Unit) {
    if (Unit) {
        Units.Add(Unit);
    }
}

void AUnitManager::RemoveUnit(AUnit* Unit) {
    if (Unit) {
        Units.Remove(Unit);
    }
}

AUnit* AUnitManager::GetUnitAtPosition(int32 X, int32 Y) const {
    for (AUnit* Unit : Units) {
        // Implementa la logica per verificare la posizione dell'unità
        // (ad esempio, confronta con le coordinate della cella)
    }
    return nullptr;
}

bool AUnitManager::IsCellOccupied(int32 X, int32 Y) const {
    for (AUnit* Unit : Units) {
        // Implementa la logica per verificare se la cella è occupata
    }
    return false;
}