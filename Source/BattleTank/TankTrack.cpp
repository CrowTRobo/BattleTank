// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


// Sets the throttle of track between -1 and +1
void UTankTrack::SetThrottle(float Throttle) {

	// Apply force to the tank's root component at track location
	FVector forceApplied = GetForwardVector() * Throttle * maxDriveForce;
	UPrimitiveComponent *tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, GetComponentLocation());
}

