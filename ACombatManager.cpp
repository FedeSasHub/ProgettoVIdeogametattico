#include "ACombatManager.h"
#include "AUnit.h"

ACombatManager::ACombatManager()
{
    PrimaryActorTick.bCanEverTick = false;
    CounterDamageMin = 1; // Danno minimo da contrattacco
    CounterDamageMax = 3; // Danno massimo da contrattacco
}

void ACombatManager::BeginPlay()
{
    Super::BeginPlay();
}

void ACombatManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ACombatManager::HandleAttack(AUnit* Attacker, AUnit* Defender)
{
    if (Attacker && Defender)
    {
        // Calcola il danno
        int32 Damage = Attacker->CalculateDamage();
        Defender->TakeDamage(Damage);

        // Log dell'attacco
        UE_LOG(LogTemp, Warning, TEXT("%s attacca %s per %d danni!"), *Attacker->GetName(), *Defender->GetName(), Damage);

        // Verifica se il difensore può contrattaccare
        if (Defender->CanCounterAttack(Attacker))
        {
            int32 CounterDamage = CalculateCounterDamage();
            Attacker->TakeDamage(CounterDamage);

            // Log del contrattacco
            UE_LOG(LogTemp, Warning, TEXT("%s contrattacca %s per %d danni!"), *Defender->GetName(), *Attacker->GetName(), CounterDamage);
        }
    }
}

int32 ACombatManager::CalculateCounterDamage() const
{
    return FMath::RandRange(CounterDamageMin, CounterDamageMax);
}