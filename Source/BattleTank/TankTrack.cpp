// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() {

	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay() {

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Calculate the slippage speed
	float slippageSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());

	// Work out the required acceleration in this frame to correct
	FVector accelCorrection = -slippageSpeed / DeltaTime * GetRightVector();

	// Calculate and apply sideways force (F = m a) - dividing by two as this will be called on both tracks
	
	if (!GetOwner()) {
		UE_LOG(LogTemp, Warning, TEXT("%f: Tick - No owner of %s"), FPlatformTime::Seconds(), *GetName());
		return;
	}

	if (!GetOwner()->GetRootComponent()) {
		UE_LOG(LogTemp, Warning, TEXT("%f: Tick - No root of %s"), FPlatformTime::Seconds(), *GetName());
		return;
	}
	
	UStaticMeshComponent *tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForce(accelCorrection * tankRoot->GetMass() / 2);
}

// Sets the throttle of track between -1 and +1
void UTankTrack::SetThrottle(float Throttle) {

	//UE_LOG(LogTemp, Warning, TEXT("%s throttle at %f"), *GetName(), Throttle)
	// Apply force to the tank's root component at track location

	if (!GetOwner()) {
		UE_LOG(LogTemp, Warning, TEXT("%f: SetThrottle - No owner of %s"), FPlatformTime::Seconds(), *GetName());
		return;
	}

	if (!GetOwner()->GetRootComponent()) {
		UE_LOG(LogTemp, Warning, TEXT("%f: SetThrottle - No root of %s"), FPlatformTime::Seconds(), *GetName());
		return;
	}

	FVector forceApplied = GetForwardVector() * Throttle * maxDriveForce;
	UPrimitiveComponent *tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	tankRoot->AddForceAtLocation(forceApplied, GetComponentLocation());
}

void UTankTrack::OnHit(UPrimitiveComponent *HitComponent, AActor * OtherActor, UPrimitiveComponent *otherComponent, FVector NormalImpulse, const FHitResult &Hit) {

	UE_LOG(LogTemp, Warning, TEXT("%d: OnHit %s"), FPlatformTime::Seconds(), *GetName());
}

