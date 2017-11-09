// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Have the tank aim at provided location
	void AimAt(FVector HitLocation, float LaunchSpeed);

	// Sets the barrel pointer to the barrel provided
	void SetBarrelReference(UTankBarrel *BarrelToSet);
	
private:
	UTankBarrel *barrel = nullptr;

	// Moves barrel to proper elevation based on aim direction
	void MoveBarrelTowards(FVector AimDirection);
};
