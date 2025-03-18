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

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void HandleAttack(AUnit* Attacker, AUnit* Defender);
    int32 CalculateCounterDamage() const;

private:
    UPROPERTY(EditAnywhere, Category = "Combat")
    int32 CounterDamageMin;

    UPROPERTY(EditAnywhere, Category = "Combat")
    int32 CounterDamageMax;
};