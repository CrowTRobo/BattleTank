// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
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


// Have the tank aim at provided location
void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {

	FVector aimDirection, launchVelocity;

	if (!barrel)
		return;

	// Calculate aim direction
	if (UGameplayStatics::SuggestProjectileVelocity(this, launchVelocity, barrel->GetSocketLocation(FName("Projectile")), HitLocation, LaunchSpeed, 
													false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {

		aimDirection = launchVelocity.GetSafeNormal();
		MoveBarrelTowards(aimDirection);
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim solved"), GetWorld()->GetTimeSeconds());
	}
	else
		UE_LOG(LogTemp, Warning, TEXT("%f: Aim not solved"), GetWorld()->GetTimeSeconds());
}


// Sets the barrel pointer to the barrel provided
void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet) {

	barrel = BarrelToSet;
}


// Sets the turret pointer to the turret provided
void UTankAimingComponent::SetTurretReference(UTankTurret *TurretToSet) {

	turret = TurretToSet;
}


// Moves barrel to proper elevation based on aim direction
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {

	// Work-out difference between current barrel rotation and AimDirection
	FRotator barrelRotator = barrel->GetForwardVector().Rotation();
	FRotator deltaRotator = AimDirection.Rotation() - barrelRotator;
	barrel->Elevate(deltaRotator.Pitch);
	turret->Turn(deltaRotator.Yaw);
}
