#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AObstacle.generated.h"

UCLASS()
class TATTICO2_API AObstacle : public AActor
{
    GENERATED_BODY()

public:
    AObstacle();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    // Variabile per identificare l'ostacolo
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle")
    bool bIsObstacle;
};