#include "AUnit.h"

AUnit::AUnit() {
    PrimaryActorTick.bCanEverTick = true;
}

void AUnit::BeginPlay() {
    Super::BeginPlay();
}

void AUnit::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

FCell AUnit::GetCurrentCell() const {
    // Implementa la logica per ottenere la cella corrente
    return FCell{ 0, 0 }; // Esempio: restituisci una cella predefinita
}

int32 AUnit::GetMovementRange() const {
    // Implementa la logica per ottenere il range di movimento
    return 3; // Esempio: range di movimento predefinito
}

int32 AUnit::CalculateDamage() const {
    return 10; // Valore base per il danno, da personalizzare
}

bool AUnit::CanCounterAttack(AUnit* Attacker) const {
    return true; // Modifica la logica per il contrattacco in base alle esigenze
}