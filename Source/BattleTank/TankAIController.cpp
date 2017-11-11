// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	ATank *controlledTank = Cast<ATank>(GetPawn());
	ATank *playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!controlledTank || !playerTank)
		return;

	controlledTank->AimAt(playerTank->GetActorLocation());
	controlledTank->Fire();
}