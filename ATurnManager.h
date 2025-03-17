#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ATurnManager.generated.h"

UCLASS()
class TATTICO2_API ATurnManager : public AActor
{
    GENERATED_BODY()

public:
    ATurnManager();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Cambia il turno
    void SwitchTurn();

    // Ottieni il turno corrente
    bool IsPlayerTurn() const;

private:
    // Variabile per tenere traccia del turno corrente
    bool bIsPlayerTurn;
};