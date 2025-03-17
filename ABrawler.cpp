#include "ABrawler.h"

ABrawler::ABrawler()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ABrawler::BeginPlay()
{
    Super::BeginPlay();
}

void ABrawler::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}