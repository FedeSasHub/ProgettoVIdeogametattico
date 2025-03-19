#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AUnit.generated.h"

UCLASS()
class TATTICO2_API AUnit : public AActor {
    GENERATED_BODY()

public:
    AUnit();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Funzione virtuale per il calcolo del danno
    virtual int32 CalculateDamage() const;
};