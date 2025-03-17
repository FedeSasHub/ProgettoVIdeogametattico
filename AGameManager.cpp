// Fill out your copyright notice in the Description page of Project Settings.


#include "AGameManager.h"

// Sets default values
AAGameManager::AAGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAGameManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

