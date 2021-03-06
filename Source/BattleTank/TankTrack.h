// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack drives the tracks of the tank to facilitate movement.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrack();

	UPROPERTY(EditDefaultsOnly)
	float maxDriveForce = 40000000.0f;  // 1 ton mass at 1g acceleration

	// Sets the throttle of track between -1 and +1
	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle(float Throttle);

private:
	float currentThrottle = 0;

	virtual void BeginPlay() override;
	
	// Apply sideways force to prevent slipping/sliding
	void ApplySidewaysForce();

	// Apply forward drive force
	void DriveTrack();

	UFUNCTION()
	void OnHit(UPrimitiveComponent *HitComponent, AActor * OtherActor, UPrimitiveComponent *otherComponent, FVector NormalImpulse, const FHitResult &Hit);
};
