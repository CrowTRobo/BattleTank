// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack() {

	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay() {

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

// Apply sideways force to prevent slipping/sliding
void UTankTrack::ApplySidewaysForce() {
	// Calculate the slippage speed
	float slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	// Work out the required acceleration in this frame to correct
	FVector accelCorrection = -slippageSpeed / GetWorld()->GetDeltaSeconds() * GetRightVector();

	// Calculate and apply sideways force (F = m a) - dividing by two as this will be called on both tracks
	UStaticMeshComponent *tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForce(accelCorrection * tankRoot->GetMass() / 2);
}

// Apply forward force to drive tank
void UTankTrack::DriveTrack() {

	// Apply force to the tank's root component at track location
	FVector forceApplied = GetForwardVector() * currentThrottle * maxDriveForce;
	UPrimitiveComponent *tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, GetComponentLocation());
}
// Sets the throttle of track between -1 and +1
void UTankTrack::SetThrottle(float Throttle) {

	currentThrottle = FMath::Clamp(currentThrottle + Throttle, -1.0f, 1.0f);
}

void UTankTrack::OnHit(UPrimitiveComponent *HitComponent, AActor * OtherActor, UPrimitiveComponent *otherComponent, FVector NormalImpulse, const FHitResult &Hit) {

	DriveTrack();
	ApplySidewaysForce();
	currentThrottle = 0;
}

