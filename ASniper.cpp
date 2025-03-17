#include "ASniper.h"

ASniper::ASniper()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ASniper::BeginPlay()
{
    Super::BeginPlay();
}

void ASniper::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}