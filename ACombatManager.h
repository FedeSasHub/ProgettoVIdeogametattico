#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AUnit.h" // Includi il file di intestazione di AUnit
#include "ACombatManager.generated.h"

UCLASS()
class TATTICO2_API ACombatManager : public AActor
{
    GENERATED_BODY()

public:
    ACombatManager();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Gestisce l'attacco tra due unità
    void HandleAttack(AUnit* Attacker, AUnit* Defender);

    // Calcola il danno da contrattacco
    int32 CalculateCounterDamage() const;

private:
    // Range di danno da contrattacco
    UPROPERTY(EditAnywhere, Category = "Combat")
    int32 CounterDamageMin;

    UPROPERTY(EditAnywhere, Category = "Combat")
    int32 CounterDamageMax;
};