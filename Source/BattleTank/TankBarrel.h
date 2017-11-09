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
	void Elevate(float degreesPerSecond);
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float maxDegreesPerSecond = 20.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float minElevationInDegrees = 0.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	float maxElevationInDegrees = 60.0f;
};