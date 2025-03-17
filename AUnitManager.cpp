#include "AUnitManager.h"
#include "AUnit.h"

AUnitManager::AUnitManager()
{
    PrimaryActorTick.bCanEverTick = false;
}

void AUnitManager::BeginPlay()
{
    Super::BeginPlay();
}

void AUnitManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AUnitManager::AddUnit(AUnit* Unit)
{
    if (Unit)
    {
        Units.Add(Unit);
        UE_LOG(LogTemp, Warning, TEXT("Unità aggiunta: %s"), *Unit->GetName());
    }
}

void AUnitManager::RemoveUnit(AUnit* Unit)
{
    if (Unit)
    {
        Units.Remove(Unit);
        UE_LOG(LogTemp, Warning, TEXT("Unità rimossa: %s"), *Unit->GetName());
    }
}

AUnit* AUnitManager::GetUnitAtPosition(int32 X, int32 Y)
{
    for (AUnit* Unit : Units)
    {
        if (Unit->GetGridPositionX() == X && Unit->GetGridPositionY() == Y)
        {
            return Unit;
        }
    }
    return nullptr;
}

bool AUnitManager::IsCellOccupied(int32 X, int32 Y)
{
    return GetUnitAtPosition(X, Y) != nullptr;
}