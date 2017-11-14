// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet) {

	barrel = BarrelToSet;
	turret = TurretToSet;
}

// Have the tank aim at provided location
void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {

	FVector aimDirection, launchVelocity;

	if (!barrel)
		return;

	// Calculate aim direction
	if (UGameplayStatics::SuggestProjectileVelocity(this, launchVelocity, barrel->GetSocketLocation(FName("ProjectileSpawn")), HitLocation, LaunchSpeed, 
													false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {

		aimDirection = launchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim not solved"), GetWorld()->GetTimeSeconds());
}


// Moves barrel to proper elevation based on aim direction
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	// Work-out difference between current barrel rotation and AimDirection
	FRotator barrelRotator = barrel->GetForwardVector().Rotation();
	FRotator deltaRotator = AimDirection.Rotation() - barrelRotator;
	barrel->Elevate(deltaRotator.Pitch);
	turret->Turn(deltaRotator.Yaw);
}


// Fire projectile
void UTankAimingComponent::Fire() {

	bool isReloaded = (FPlatformTime::Seconds() - lastFireTime) > reloadTimeInSecs;

	if (barrel && isReloaded) {
		// Spawn projectile at the location of the socket on the barrel
		AProjectile *projectile = GetWorld()->SpawnActor<AProjectile>(projectileBP,
			barrel->GetSocketLocation(FName("ProjectileSpawn")),
			barrel->GetSocketRotation(FName("ProjectileSpawn")));

		projectile->LaunchProjectile(launchSpeed);
		lastFireTime = FPlatformTime::Seconds();
	}
}

