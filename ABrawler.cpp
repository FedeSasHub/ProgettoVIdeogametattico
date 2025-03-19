#include "ABrawler.h"

ABrawler::ABrawler() {
    PrimaryActorTick.bCanEverTick = true;
}

void ABrawler::BeginPlay() {
    Super::BeginPlay();
}

void ABrawler::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

int32 ABrawler::CalculateDamage() const {
    // Implementazione specifica per Brawler
    return FMath::RandRange(1, 6); // Danno casuale tra 1 e 6
}