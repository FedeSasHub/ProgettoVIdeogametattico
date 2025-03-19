#include "ACombatManager.h"

ACombatManager::ACombatManager() {
    PrimaryActorTick.bCanEverTick = true;
}

void ACombatManager::BeginPlay() {
    Super::BeginPlay();
}

void ACombatManager::HandleAttack(AUnit* Attacker, AUnit* Defender) {
    if (Defender && Defender->CanCounterAttack(Attacker)) {
        int32 CounterDamage = CalculateCounterDamage(Defender);
        // Applica il danno da contrattacco qui
    }
}

int32 ACombatManager::CalculateCounterDamage(AUnit* Defender) const {
    return 5; // Danno base per il contrattacco
}
