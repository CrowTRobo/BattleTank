// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	UTankAimingComponent *aimingComponent = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, Category = Firing)
	float launchSpeed = 4000.0f;

	UPROPERTY(EditAnywhere, Category = Firing)
	TSubclassOf<AProjectile> projectileBP;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Have the tank aim at provided location
	void AimAt(FVector HitLocation);

	// Sets the barrel pointer in the Aiming Component to the barrel provided
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrelReference(UTankBarrel *BarrelToSet);

	// Sets the turret pointer in the Aiming Component to the turret provided
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurretReference(UTankTurret *TurretToSet);

	// Fire projectile
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Fire();

private:
	UTankBarrel *barrel = nullptr;
};
