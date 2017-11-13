// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	aimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("AimingComponent"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


// Have the tank aim at provided location
void ATank::AimAt(FVector HitLocation) {

	aimingComponent->AimAt(HitLocation, launchSpeed);
}


// Sets the barrel pointer in the Aiming Component to the barrel provided
void ATank::SetBarrelReference(UTankBarrel * BarrelToSet) {

	aimingComponent->SetBarrelReference(BarrelToSet);
	barrel = BarrelToSet;
}


// Sets the turret pointer in the Aiming Component to the turret provided
void ATank::SetTurretReference(UTankTurret * TurretToSet) {

	aimingComponent->SetTurretReference(TurretToSet);
}

// Fire projectile
void ATank::Fire() {

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



