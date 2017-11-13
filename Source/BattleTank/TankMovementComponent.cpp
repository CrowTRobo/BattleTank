// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialize(UTankTrack *LeftTrackToSet, UTankTrack *RightTrackToSet) {

	if (!LeftTrackToSet || !RightTrackToSet)
		return;

	leftTrack = LeftTrackToSet;
	rightTrack = RightTrackToSet;

}


void UTankMovementComponent::IntendMoveForward(float Throw) {

	leftTrack->SetThrottle(Throw);
	rightTrack->SetThrottle(Throw);
}

