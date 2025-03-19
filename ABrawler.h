#pragma once

#include "CoreMinimal.h"
#include "AUnit.h" // Includi il file della classe genitore
#include "ABrawler.generated.h"

UCLASS()
class TATTICO2_API ABrawler : public AUnit {
    GENERATED_BODY()

public:
    ABrawler();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Override del calcolo del danno
    virtual int32 CalculateDamage() const override;
};