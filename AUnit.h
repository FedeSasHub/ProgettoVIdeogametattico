#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGrid.h"  // Includi AGrid per usare FCell
#include "AUnit.generated.h"

UCLASS()
class TATTICO2_API AUnit : public AActor {
    GENERATED_BODY()

public:
    AUnit();

    // Ottiene la cella corrente
    FCell GetCurrentCell() const;

    // Ottiene il range di movimento
    int32 GetMovementRange() const;

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Funzione virtuale per il calcolo del danno
    virtual int32 CalculateDamage() const;

    // Funzione per verificare se l'unità può contrattaccare
    virtual bool CanCounterAttack(AUnit* Attacker) const;
};