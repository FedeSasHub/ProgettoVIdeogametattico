#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AGrid.generated.h"

UCLASS()
class TATTICO2_API AGrid : public AActor
{
    GENERATED_BODY()

public:
    AGrid();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Genera la griglia
    void GenerateGrid();

    // Genera gli ostacoli
    void GenerateObstacles(float ObstaclePercentage);

    // Disegna la griglia (debug)
    void DrawGrid();

    // Ottieni la posizione di una cella
    FVector GetCellPosition(int32 X, int32 Y) const;

    // Verifica se una cella è valida
    bool IsCellValid(int32 X, int32 Y) const;

    // Verifica se una cella è occupata da un ostacolo
    bool IsCellObstacle(int32 X, int32 Y) const;

    // Verifica se una cella è occupata da un'unità
    bool IsCellOccupied(int32 X, int32 Y) const;

    // Verifica se la griglia è completamente raggiungibile
    bool IsGridFullyReachable() const;

    // Riferimento al UnitManager
    UPROPERTY()
    class AUnitManager* UnitManager;

private:
    // Dimensioni della griglia
    UPROPERTY(EditAnywhere, Category = "Grid")
    int32 GridSize;

    // Dimensioni di ogni cella
    UPROPERTY(EditAnywhere, Category = "Grid")
    float CellSize;

    // Array per memorizzare le celle
    TArray<TArray<FVector>> GridArray;

    // Array per memorizzare gli ostacoli
    TArray<TArray<bool>> ObstacleGrid;

    // Classe per gli ostacoli
    UPROPERTY(EditAnywhere, Category = "Grid")
    TSubclassOf<class AObstacle> ObstacleClass;

    // Contatore degli ostacoli
    int32 ObstacleCount;
};