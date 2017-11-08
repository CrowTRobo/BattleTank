// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("PlayerController has possessed: %s"), *GetControlledTank()->GetName());
}


void ATankPlayerController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


ATank *ATankPlayerController::GetControlledTank() const {

	return Cast<ATank>(GetPawn());
}


// Aims barrel at point in world where the crosshair pointing at.

void ATankPlayerController::AimTowardsCrosshair() {

	if (!GetControlledTank())
		return;

	FVector hitLocation;

	if (GetSightRayHitLocation(hitLocation)) {
		//UE_LOG(LogTemp, Warning, TEXT("Hit Location: %s"), *hitLocation.ToString());
	}
}


// Traces ray from crosshair to world and obtains the location of the hit

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const {

	int32 xViewportSize, yViewportSize;
	FVector worldLocation, worldDirection;
	
	// Get the crosshair location in pixels
	GetViewportSize(xViewportSize, yViewportSize);
	FVector2D screenLocation((float)xViewportSize * xCrosshairLocation, (float)yViewportSize * yCrosshairLocation);

	// Deproject the screen location to a world direction
	DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, worldLocation, worldDirection);

	UE_LOG(LogTemp, Warning, TEXT("World direction: %s"), *worldDirection.ToString());

	OutHitLocation = FVector(1.0f);
	return true;
}