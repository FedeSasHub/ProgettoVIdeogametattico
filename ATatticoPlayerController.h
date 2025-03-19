#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AGrid.h" // Includi il file di intestazione di AGrid
#include "AUnit.h"
#include "ATatticoPlayerController.generated.h"


UCLASS()
class TATTICO2_API ATatticoPlayerController : public APlayerController {
    GENERATED_BODY()

public:
    ATatticoPlayerController();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Evidenzia il range di movimento di una unità
    void HighlightMovementRange(AUnit* SelectedUnit);

private:
    AGrid* Grid;
};