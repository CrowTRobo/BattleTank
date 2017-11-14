// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay() {

	Super::BeginPlay();

	UTankAimingComponent *aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (aimingComponent)
		FoundAimingComponent(aimingComponent);
	else
		UE_LOG(LogTemp, Warning, TEXT("Player Controller can't find Aiming Component"))
}


void ATankPlayerController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}


// Aims barrel at point in world where the crosshair pointing at.

void ATankPlayerController::AimTowardsCrosshair() {

	UTankAimingComponent *aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(aimingComponent))
		return;

	FVector hitLocation;

	if (GetSightRayHitLocation(hitLocation)) {
		aimingComponent->AimAt(hitLocation);
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