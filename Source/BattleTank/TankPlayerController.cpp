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
		GetControlledTank()->AimAt(hitLocation);
	}
}


// Traces ray from crosshair to world and obtains the location of the hit

bool ATankPlayerController::GetSightRayHitLocation(FVector &OutHitLocation) const {

	int32 xViewportSize, yViewportSize;
	FVector worldLocation, worldDirection;
	FHitResult hitResult;
	
	// Get the crosshair location in pixels
	GetViewportSize(xViewportSize, yViewportSize);
	FVector2D screenLocation((float)xViewportSize * xCrosshairLocation, (float)yViewportSize * yCrosshairLocation);

	// Deproject the screen location to a world direction
	if (DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, worldLocation, worldDirection)) {

		if (GetWorld()->LineTraceSingleByChannel(hitResult, worldLocation, worldLocation + worldDirection * lineTraceRange, ECC_Visibility)) {
			OutHitLocation = hitResult.Location;
			return true;
		}
	}

	OutHitLocation = FVector(0);
	return false;
}