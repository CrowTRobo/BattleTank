// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AIController has found player: %s"), *GetPlayerTank()->GetName())
}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	ATank *controlledTank = GetControlledTank();
	ATank *playerTank = GetPlayerTank();

	if (!controlledTank || !playerTank)
		return;

	controlledTank->AimAt(playerTank->GetActorLocation());
}

ATank *ATankAIController::GetControlledTank() const {
	
	return Cast<ATank>(GetPawn());
}

ATank *ATankAIController::GetPlayerTank() const {

	auto *playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!playerTank)
		return nullptr;

	return Cast<ATank>(playerTank);
}
