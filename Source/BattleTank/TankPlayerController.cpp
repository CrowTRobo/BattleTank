// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("PlayerController has possessed: %s"), *GetControlledTank()->GetName())
}


void ATankPlayerController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);


}


ATank *ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}


// Aims barrel at point in world where the crosshair pointing at.

void ATankPlayerController::AimTowardsCrosshair() {

	if (!GetControlledTank())
		return;


}