#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AUnit.generated.h"

UCLASS()
class TATTICO2_API AUnit : public AActor
{
    GENERATED_BODY()

public:
    AUnit();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Imposta la posizione sulla griglia
    void SetGridPosition(int32 X, int32 Y);

    // Ottieni la posizione X sulla griglia
    int32 GetGridPositionX() const;

    // Ottieni la posizione Y sulla griglia
    int32 GetGridPositionY() const;

    // Calcola il danno
    int32 CalculateDamage() const;

    // Applica il danno all'unità
    void TakeDamage(int32 Damage);

    // Verifica se l'unità può contrattaccare
    bool CanCounterAttack(AUnit* Attacker) const;

private:
    // Posizione sulla griglia
    int32 GridPositionX;
    int32 GridPositionY;

    // Punti vita dell'unità
    UPROPERTY(EditAnywhere, Category = "Unit")
    int32 Health;

    // Danno minimo e massimo
    UPROPERTY(EditAnywhere, Category = "Unit")
    int32 DamageMin;

    UPROPERTY(EditAnywhere, Category = "Unit")
    int32 DamageMax;
};