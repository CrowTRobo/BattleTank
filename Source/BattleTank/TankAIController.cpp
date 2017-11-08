// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AIController has found player: %s"), *GetPlayerTank()->GetName())
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
