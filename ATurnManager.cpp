#include "ATurnManager.h"

ATurnManager::ATurnManager()
{
    PrimaryActorTick.bCanEverTick = false;
    bIsPlayerTurn = true; // Il giocatore inizia per primo
}

void ATurnManager::BeginPlay()
{
    Super::BeginPlay();
}

void ATurnManager::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATurnManager::SwitchTurn()
{
    bIsPlayerTurn = !bIsPlayerTurn;
    UE_LOG(LogTemp, Warning, TEXT("Turno cambiato: %s"), bIsPlayerTurn ? TEXT("Player") : TEXT("AI"));
}

bool ATurnManager::IsPlayerTurn() const
{
    return bIsPlayerTurn;
}