#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AUnit.generated.h"

UCLASS()
class YOURPROJECTNAME_API AAUnit : public AActor {
    GENERATED_BODY()

public:
    AAUnit();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Muove l'unità a una cella specifica
    void MoveToCell(FCell Destination);

    // Ottiene la cella corrente
    FCell GetCurrentCell() const { return CurrentCell; }

    // Imposta la cella corrente
    void SetCurrentCell(FCell Cell) { CurrentCell = Cell; }

    // Ottiene il range di movimento
    int32 GetMovementRange() const { return MovementRange; }

private:
    FCell CurrentCell;
    int32 MovementRange;
};