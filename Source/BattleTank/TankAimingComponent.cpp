// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


// Have the tank aim at provided location
void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {

	FVector aimDirection, launchVelocity;

	if (!barrel)
		return;

	// Calculate aim direction
	if (UGameplayStatics::SuggestProjectileVelocity(this, launchVelocity, barrel->GetSocketLocation(FName("Projectile")), HitLocation, LaunchSpeed)) {
		aimDirection = launchVelocity.GetSafeNormal();
		UE_LOG(LogTemp, Warning, TEXT("Aiming at %s"), *aimDirection.ToString());
	}
}

// Sets the barrel pointer to the barrel provided
void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet) {

	barrel = BarrelToSet;
}
