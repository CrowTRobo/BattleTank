// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Tank.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	ATank *GetControlledTank() const;

	// Aims barrel at point in world where the crosshair pointing at.
	void AimTowardsCrosshair();
	
	// Traces ray from crosshair to world and obtains the location of the hit
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
};
