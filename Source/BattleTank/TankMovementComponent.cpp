// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet) {

	leftTrack = LeftTrackToSet;
	rightTrack = RightTrackToSet;

}


void UTankMovementComponent::IntendMoveForward(float Throw) {

	if (!leftTrack || !rightTrack)
		return;

	leftTrack->SetThrottle(Throw);
	rightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {

	if (!leftTrack || !rightTrack)
		return;

	leftTrack->SetThrottle(Throw);
	rightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) {

	//UE_LOG(LogTemp, Warning, TEXT("%s MoveVelocity = %s"), *GetOwner()->GetName(), *MoveVelocity.ToString())

	IntendMoveForward(FVector::DotProduct(MoveVelocity.GetSafeNormal(), GetOwner()->GetActorForwardVector()));
}

