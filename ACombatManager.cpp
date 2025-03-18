#include "ACombatManager.h"
#include "Engine.h"
#include "AUnit.h"
#include "GameFramework/DamageType.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/Controller.h"


ACombatManager::ACombatManager()
{
    PrimaryActorTick.bCanEverTick = false;
    CounterDamageMin = 1;
    CounterDamageMax = 3;
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

        // Crea un FDamageEvent
        FDamageEvent DamageEvent;

        // Applica il danno al difensore
        Defender->TakeDamage(Damage, DamageEvent, Cast<AActor>(Attacker)->GetInstigatorController(), Attacker);

        // Log dell'attacco
        UE_LOG(LogTemp, Warning, TEXT("%s attacca %s per %d danni!"), *Attacker->GetName(), *Defender->GetName(), Damage);

        // Verifica se il difensore può contrattaccare
        if (Defender->CanCounterAttack(Attacker))
        {
            int32 CounterDamage = CalculateCounterDamage();

            // Applica il danno da contrattacco all'attaccante
            Attacker->TakeDamage(CounterDamage, DamageEvent, Cast<AActor>(Defender)->GetInstigatorController(), Defender);

            // Log del contrattacco
            UE_LOG(LogTemp, Warning, TEXT("%s contrattacca %s per %d danni!"), *Defender->GetName(), *Attacker->GetName(), CounterDamage);
        }
    }
}

int32 ACombatManager::CalculateCounterDamage() const
{
    return FMath::RandRange(CounterDamageMin, CounterDamageMax);
}