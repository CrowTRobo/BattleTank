// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

// Move the barrel the right amount this frame using max elevation speed
void UTankTurret::Turn(float RelativeSpeed) {

	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);
	float rotationChange = RelativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float newRotation = RelativeRotation.Yaw + rotationChange;

	SetRelativeRotation(FRotator(0.0f, newRotation, 0.0f));
}


