#include "ASniper.h"
#include "ABrawler.h"

ASniper::ASniper()
{
    // Imposta le proprietà specifiche dello Sniper
    MovementRange = 3;
    AttackType = 1;
    AttackRange = 10;
    DamageMin = 4;
    DamageMax = 8;
    Health = 20;
}

void ASniper::BeginPlay()
{
    Super::BeginPlay();
}

void ASniper::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

int32 ASniper::CalculateDamage() const
{
    return FMath::RandRange(DamageMin, DamageMax);
}

bool ASniper::CanCounterAttack(AUnit* Attacker) const
{
    // Lo Sniper può contrattaccare solo se attaccato da un altro Sniper o da un Brawler a distanza 1
    if (Attacker->GetClass() == ASniper::StaticClass())
    {
        return true;
    }
    if (Attacker->GetClass() == ABrawler::StaticClass() &&
        FMath::Abs(GetGridPositionX() - Attacker->GetGridPositionX()) +
        FMath::Abs(GetGridPositionY() - Attacker->GetGridPositionY()) == 1)
    {
        return true;
    }
    return false;
}