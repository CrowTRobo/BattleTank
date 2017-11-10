// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"

// Move the barrel the right amount this frame using max elevation speed
void UTankBarrel::Elevate(float RelativeSpeed) {

	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	float elevationChange = RelativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float newElevation = FMath::Clamp(RelativeRotation.Pitch + elevationChange, minElevationInDegrees, maxElevationInDegrees);

	SetRelativeRotation(FRotator(newElevation, 0.0f, 0.0f));
}

