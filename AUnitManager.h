#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AUnit.h" // Includi il file di intestazione di AUnit
#include "AUnitManager.generated.h"

UCLASS()
class TATTICO2_API AUnitManager : public AActor
{
    GENERATED_BODY()

public:
    AUnitManager();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Aggiunge un'unità al manager
    void AddUnit(AUnit* Unit);

    // Rimuove un'unità dal manager
    void RemoveUnit(AUnit* Unit);

    // Trova un'unità in una specifica cella
    AUnit* GetUnitAtPosition(int32 X, int32 Y) const;

    // Verifica se una cella è occupata
    bool IsCellOccupied(int32 X, int32 Y) const;

private:
    // Array per memorizzare tutte le unità
    UPROPERTY()
    TArray<AUnit*> Units;
};