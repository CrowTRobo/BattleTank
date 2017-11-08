// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("PlayerController has possessed: %s"), *GetControlledTank()->GetName())
}

ATank *ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}

