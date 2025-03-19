#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGrid.generated.h"

USTRUCT()
struct FCell {
    GENERATED_BODY()

    int32 X;
    int32 Y;
    int32 GCost;
    int32 HCost;
    FCell* Parent;

    int32 GetFCost() const { return GCost + HCost; }
};

UCLASS()
class YOURPROJECTNAME_API AAGrid : public AActor {
    GENERATED_BODY()

public:
    AAGrid();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Genera la griglia
    void GenerateGrid();

    // Trova il percorso minimo tra due celle
    TArray<FCell> FindPath(FCell Start, FCell Goal);

    // Verifica se tutte le celle sono raggiungibili
    bool IsGridFullyReachable();

    // Ottiene le celle vicine
    TArray<FCell> GetNeighbors(FCell Cell);

    // Ottiene la distanza tra due celle
    int32 GetDistance(FCell A, FCell B);

    // Evidenzia una cella
    void HighlightCell(FCell Cell, FColor Color);

    // Ottiene la posizione mondiale di una cella
    FVector GetCellWorldPosition(FCell Cell);

    // Verifica se una cella è bloccata
    bool IsBlocked(FCell Cell);

private:
    UPROPERTY(EditAnywhere, Category = "Grid")
    int32 GridSizeX;

    UPROPERTY(EditAnywhere, Category = "Grid")
    int32 GridSizeY;

    UPROPERTY(EditAnywhere, Category = "Grid")
    float CellSize;

    TArray<TArray<FCell>> GridCells;
};