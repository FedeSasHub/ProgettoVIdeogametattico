#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "APlayerController.generated.h"

UCLASS()
class YOURPROJECTNAME_API AAPlayerController : public APlayerController {
    GENERATED_BODY()

public:
    AAPlayerController();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Evidenzia il range di movimento di una unità
    void HighlightMovementRange(AAUnit* SelectedUnit);

private:
    AAGrid* Grid;
};