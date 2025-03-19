#pragma once

#include "CoreMinimal.h" // Assicurati che sia incluso
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
    bool bIsObstacle;

    FCell() : X(0), Y(0), GCost(0), HCost(0), Parent(nullptr), bIsObstacle(false) {}
    FCell(int32 InX, int32 InY) : X(InX), Y(InY), GCost(0), HCost(0), Parent(nullptr), bIsObstacle(false) {}

    int32 GetFCost() const { return GCost + HCost; }

    // Operatore di uguaglianza
    bool operator==(const FCell& Other) const {
        return X == Other.X && Y == Other.Y;
    }
};

// Definisci GetTypeHash per FCell
inline uint32 GetTypeHash(const FCell& Cell) {
    // Combina X e Y in un unico valore hash
    return HashCombine(GetTypeHash(Cell.X), GetTypeHash(Cell.Y));
}

UCLASS()
class TATTICO2_API AGrid : public AActor {
    GENERATED_BODY()

public:
    AGrid();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Genera la griglia
    void GenerateGrid();

    // Trova il percorso minimo tra due celle
    TArray<FCell> FindPath(FCell Start, FCell Goal);

    // Verifica se tutte le celle sono raggiungibili
    bool IsGridFullyReachable() const;

    // Ottiene le celle vicine
    TArray<FCell> GetNeighbors(FCell Cell) const;

    // Ottiene la distanza tra due celle
    int32 GetDistance(FCell A, FCell B) const;

    // Evidenzia una cella
    void HighlightCell(FCell Cell, FColor Color);

    // Ottiene la posizione mondiale di una cella
    FVector GetCellWorldPosition(FCell Cell) const;

    // Verifica se una cella è bloccata
    bool IsBlocked(FCell Cell) const;

    // Ottiene le celle raggiungibili
    TArray<FCell> GetReachableCells(FCell StartCell, int32 Range) const;

    // Ottiene l'oggetto della cella
    AActor* GetCellActor(FCell Cell) const;

    // Verifica se una cella è valida
    bool IsValidCell(FCell Cell) const;

    // Blueprint della cella
    UPROPERTY(EditAnywhere, Category = "Grid")
    TSubclassOf<AActor> CellBlueprintClass;

private:
    UPROPERTY(EditAnywhere, Category = "Grid")
    int32 GridSizeX;

    UPROPERTY(EditAnywhere, Category = "Grid")
    int32 GridSizeY;

    UPROPERTY(EditAnywhere, Category = "Grid")
    float CellSize;

    TArray<TArray<FCell>> GridCells;

    // Array per memorizzare gli oggetti delle celle
    TArray<TArray<AActor*>> GridActors;
};