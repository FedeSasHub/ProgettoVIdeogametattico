#include "AObstacle.h"

AObstacle::AObstacle()
{
    PrimaryActorTick.bCanEverTick = false;
    bIsObstacle = true; // Imposta come ostacolo di default
}

void AObstacle::BeginPlay()
{
    Super::BeginPlay();
}

void AObstacle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}