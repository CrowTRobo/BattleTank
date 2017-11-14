// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	APawn *controlledTank = GetPawn();
	APawn *playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	UTankAimingComponent *aimingComponent = controlledTank->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(controlledTank || playerTank || aimingComponent)) {
		return;
	}

	// Move tank towards player
	EPathFollowingRequestResult::Type result = MoveToActor(playerTank, acceptanceRadius);
	
	/*if (result == EPathFollowingRequestResult::Failed)
		UE_LOG(LogTemp, Warning, TEXT("%s path following result: Failed"), *controlledTank->GetName())
	else if (result == EPathFollowingRequestResult::AlreadyAtGoal)
		UE_LOG(LogTemp, Warning, TEXT("%s path following result: AlreadyAtGoal"), *controlledTank->GetName())
	else
		UE_LOG(LogTemp, Warning, TEXT("%s path following result: RequestSuccessful"), *controlledTank->GetName())*/

	// Aim and fire at player
	aimingComponent->AimAt(playerTank->GetActorLocation());
	aimingComponent->Fire();
}