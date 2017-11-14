// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankPlayerController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay() {

	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime) {

	Super::Tick(DeltaTime);

	ATank *controlledTank = Cast<ATank>(GetPawn());
	ATank *playerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (!controlledTank || !playerTank) {
		UE_LOG(LogTemp, Warning, TEXT("TankAIController::Tick - pointers null"))
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
	controlledTank->AimAt(playerTank->GetActorLocation());
	//controlledTank->Fire();
}