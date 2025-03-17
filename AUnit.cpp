#include "AUnit.h"

AUnit::AUnit()
{
    PrimaryActorTick.bCanEverTick = false;
    GridPositionX = -1;
    GridPositionY = -1;
    Health = 100; // Punti vita di default
    DamageMin = 1; // Danno minimo di default
    DamageMax = 10; // Danno massimo di default
}

void AUnit::BeginPlay()
{
    Super::BeginPlay();
}

void AUnit::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AUnit::SetGridPosition(int32 X, int32 Y)
{
    GridPositionX = X;
    GridPositionY = Y;
}

int32 AUnit::GetGridPositionX() const
{
    return GridPositionX;
}

int32 AUnit::GetGridPositionY() const
{
    return GridPositionY;
}

int32 AUnit::CalculateDamage() const
{
    return FMath::RandRange(DamageMin, DamageMax);
}

void AUnit::TakeDamage(int32 Damage)
{
    Health -= Damage;
    if (Health <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s è stato eliminato!"), *GetName());
        Destroy();
    }
}

bool AUnit::CanCounterAttack(AUnit* Attacker) const
{
    // Controlla se l'unità può contrattaccare (es. solo se è uno Sniper o un Brawler a distanza 1)
    return true; // Implementa la logica specifica qui
}