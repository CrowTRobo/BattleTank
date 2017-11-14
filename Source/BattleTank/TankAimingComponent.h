// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringStatus : uint8 {Locked, Aiming, Reloading};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Have the tank aim at provided location
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet);

	// Fire projectile
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();

private:
	UTankBarrel *barrel = nullptr;
	UTankTurret *turret = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float reloadTimeInSecs = 3.0f;

	double lastFireTime = 0;

	// Moves barrel to proper elevation based on aim direction
	void MoveBarrelTowards(FVector AimDirection);

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringStatus firingStatus = EFiringStatus::Locked;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float launchSpeed = 4000.0f;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	TSubclassOf<AProjectile> projectileBP;
};
