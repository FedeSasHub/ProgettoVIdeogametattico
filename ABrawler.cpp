#include "ABrawler.h"

ABrawler::ABrawler()
{
    // Imposta le proprietà specifiche del Brawler
    MovementRange = 6; // Max 6 celle
    AttackType = 0; // Attacco a corto raggio
    AttackRange = 1; // Max 1 cella
    DamageMin = 1; // Danno minimo
    DamageMax = 6; // Danno massimo
    Health = 40; // Punti vita
}

void ABrawler::BeginPlay()
{
    Super::BeginPlay();
}

void ABrawler::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

int32 ABrawler::CalculateDamage() const
{
    return FMath::RandRange(DamageMin, DamageMax);
}