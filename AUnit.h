#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/DamageType.h"
#include "AUnit.generated.h"

UCLASS()
class TATTICO2_API AUnit : public APawn
{
    GENERATED_BODY()

public:
    AUnit();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    void SetGridPosition(int32 X, int32 Y);
    int32 GetGridPositionX() const;
    int32 GetGridPositionY() const;
    virtual int32 CalculateDamage() const;
    virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
    virtual bool CanCounterAttack(AUnit* Attacker) const;
    bool MoveTo(int32 TargetX, int32 TargetY, class AGrid* Grid);
    int32 GetMovementRange() const;
    AController* GetUnitController() const;

protected:
    int32 GridPositionX;
    int32 GridPositionY;

    UPROPERTY(EditAnywhere, Category = "Unit")
    int32 Health;

    UPROPERTY(EditAnywhere, Category = "Unit")
    int32 DamageMin;

    UPROPERTY(EditAnywhere, Category = "Unit")
    int32 DamageMax;

    UPROPERTY(EditAnywhere, Category = "Unit")
    int32 MovementRange;

    UPROPERTY(EditAnywhere, Category = "Unit")
    int32 AttackType;

    UPROPERTY(EditAnywhere, Category = "Unit")
    int32 AttackRange;

    AController* UnitController;
};
