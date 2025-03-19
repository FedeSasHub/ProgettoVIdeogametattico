#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AUnit.h"
#include "ACombatManager.generated.h"

UCLASS()
class TATTICO2_API ACombatManager : public AActor
{
    GENERATED_BODY()

public:
    ACombatManager();
    void HandleAttack(AUnit* Attacker, AUnit* Defender);
    int32 CalculateCounterDamage(AUnit* Defender) const;

protected:
    virtual void BeginPlay() override;

private:
    int32 CounterDamageMin;
    int32 CounterDamageMax;
};
