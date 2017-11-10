// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"

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
}


// Sets the turret pointer in the Aiming Component to the turret provided
void ATank::SetTurretReference(UTankTurret * TurretToSet) {

	aimingComponent->SetTurretReference(TurretToSet);
}
