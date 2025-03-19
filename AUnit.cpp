#include "AUnit.h"

AUnit::AUnit() {
    PrimaryActorTick.bCanEverTick = true;
}

void AUnit::BeginPlay() {
    Super::BeginPlay();
}

void AUnit::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

int32 AUnit::CalculateDamage() const {
    // Implementazione di base per il calcolo del danno
    return 0;
}