// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	ATank *GetControlledTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent *AimCompRef);

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	float xCrosshairLocation = 0.5f;

	UPROPERTY(EditAnywhere)
	float yCrosshairLocation = 0.33333f;

	UPROPERTY(EditAnywhere)
	float lineTraceRange = 1000000.0f;  // 10km

	// Aims barrel at point in world where the crosshair pointing at.
	void AimTowardsCrosshair();
	
	// Traces ray from crosshair to world and obtains the location of the hit
	bool GetSightRayHitLocation(FVector &OutHitLocation) const;
};
