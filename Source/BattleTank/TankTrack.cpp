// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


// Sets the throttle of track between -1 and +1
void UTankTrack::SetThrottle(float Throttle) {

	UE_LOG(LogTemp, Warning, TEXT("%s throttle set to %f"), *GetName(), Throttle);
}

