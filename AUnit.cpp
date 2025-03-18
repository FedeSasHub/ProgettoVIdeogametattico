#include "AUnit.h"
#include "AGrid.h"
#include "GameFramework/DamageType.h" // Assicura che FDamageEvent sia riconosciuto

AUnit::AUnit()
{
    PrimaryActorTick.bCanEverTick = false;
    GridPositionX = -1;
    GridPositionY = -1;
    Health = 100;
    DamageMin = 1;
    DamageMax = 10;
    MovementRange = 3;
    AttackType = 0;
    AttackRange = 1;
}

void AUnit::BeginPlay()
{
    Super::BeginPlay();
    UnitController = GetController();
}

void AUnit::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AUnit::SetGridPosition(int32 X, int32 Y)
{
    GridPositionX = X;
    GridPositionY = Y;
}

int32 AUnit::GetGridPositionX() const
{
    return GridPositionX;
}

int32 AUnit::GetGridPositionY() const
{
    return GridPositionY;
}

int32 AUnit::CalculateDamage() const
{
    return FMath::RandRange(DamageMin, DamageMax);
}

float AUnit::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
    Health -= DamageAmount;
    if (Health <= 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("%s è stato eliminato!"), *GetName());
        Destroy();
    }
    return DamageAmount;
}

bool AUnit::CanCounterAttack(AUnit* Attacker) const
{
    return true;
}

bool AUnit::MoveTo(int32 TargetX, int32 TargetY, AGrid* Grid)
{
    if (!Grid || !Grid->IsCellValid(TargetX, TargetY)) return false;

    if (Grid->IsCellObstacle(TargetX, TargetY) || Grid->IsCellOccupied(TargetX, TargetY))
    {
        return false;
    }

    int32 Distance = FMath::Abs(TargetX - GridPositionX) + FMath::Abs(TargetY - GridPositionY);
    if (Distance > MovementRange)
    {
        return false;
    }

    GridPositionX = TargetX;
    GridPositionY = TargetY;
    FVector NewLocation = Grid->GetCellPosition(TargetX, TargetY);
    SetActorLocation(NewLocation);
    return true;
}

int32 AUnit::GetMovementRange() const
{
    return MovementRange;
}

AController* AUnit::GetUnitController() const
{
    return UnitController;
}