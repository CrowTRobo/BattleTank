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

void UTankAimingComponent::BeginPlay() {

	Super::BeginPlay();

	// Set now so that initial firing is after reload time
	lastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (roundsLeft <= 0) {
		firingStatus = EFiringStatus::Empty;
	}
	else if ((FPlatformTime::Seconds() - lastFireTime) < reloadTimeInSecs) {
		firingStatus = EFiringStatus::Reloading;
	}
	else if (IsBarrelMoving()) {
		firingStatus = EFiringStatus::Aiming;
	}
	else {
		firingStatus = EFiringStatus::Locked;
	}
}

void UTankAimingComponent::Initialize(UTankBarrel *BarrelToSet, UTankTurret *TurretToSet) {

	barrel = BarrelToSet;
	turret = TurretToSet;
}

EFiringStatus UTankAimingComponent::GetFiringStatus() const {

	return firingStatus;
}

int32 UTankAimingComponent::GetRoundsLeft() const {

	return roundsLeft;
}
// Have the tank aim at provided location
void UTankAimingComponent::AimAt(FVector HitLocation) {

	FVector aimDirection, launchVelocity;

	if (!ensure(barrel))
		return;

	// Calculate aim direction
	if (UGameplayStatics::SuggestProjectileVelocity(this, launchVelocity, barrel->GetSocketLocation(FName("ProjectileSpawn")), HitLocation, launchSpeed, 
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

	// Use GetNormalized to prevent turret from rotating the long way around
	barrel->Elevate(deltaRotator.GetNormalized().Pitch);
	turret->Turn(deltaRotator.GetNormalized().Yaw);

	// Store AimDirection for IsBarrelMoving() to use
	aimingDirection = AimDirection;
}


// Fire projectile
void UTankAimingComponent::Fire() {

	if (!ensure(barrel || projectileBP))
		return;

	if (firingStatus != EFiringStatus::Reloading && roundsLeft > 0) {
		// Spawn projectile at the location of the socket on the barrel
		AProjectile *projectile = GetWorld()->SpawnActor<AProjectile>(projectileBP,
			barrel->GetSocketLocation(FName("ProjectileSpawn")),
			barrel->GetSocketRotation(FName("ProjectileSpawn")));

		projectile->LaunchProjectile(launchSpeed);
		lastFireTime = FPlatformTime::Seconds();
		roundsLeft--;
	}
}

// Determines whether barrel is currently moving

bool UTankAimingComponent::IsBarrelMoving() {

	if (!ensure(barrel))
		return false;

	return !barrel->GetForwardVector().Equals(aimingDirection, 0.01f);
}
