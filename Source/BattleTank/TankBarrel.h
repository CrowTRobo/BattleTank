// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

// Holds barrel properties and method to change elevation
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, +1 is max up 
	void Elevate(float RelativeSpeed);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxDegreesPerSecond = 5.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float minElevationInDegrees = 0.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float maxElevationInDegrees = 40.0f;
};
