#include "ASniper.h"

ASniper::ASniper() {
    PrimaryActorTick.bCanEverTick = true;
}

void ASniper::BeginPlay() {
    Super::BeginPlay();
}

void ASniper::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

int32 ASniper::CalculateDamage() const {
    // Implementazione specifica per Sniper
    return FMath::RandRange(4, 8); // Danno casuale tra 4 e 8
}