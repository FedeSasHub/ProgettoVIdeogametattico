#pragma once

#include "CoreMinimal.h"
#include "AUnit.h"
#include "ASniper.generated.h"

UCLASS()
class TATTICO2_API ASniper : public AUnit
{
    GENERATED_BODY()

public:
    ASniper();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;
};