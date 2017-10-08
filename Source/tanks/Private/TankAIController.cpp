// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"


void ATankAIController::BeginPlay() {
    Super::BeginPlay();
}

void ATankAIController::Tick(float deltaTime) {
    Super::Tick(deltaTime);

    auto playerTank = getPlayerTank();
    auto ownTank = GetPawn();
    if (!ensure(playerTank && ownTank)) return;
    
    auto playerLocation = playerTank->GetActorLocation();
    
    MoveToActor(playerTank, HowFarAwayICanStopMpvingTowardsTheGoal);
    
    auto aimingComponent = ownTank->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(aimingComponent)) {return;}
    
    aimingComponent->aimAt(playerLocation);
	auto fireState = aimingComponent->GetCrosshairState();
	if (fireState  == ECrosshairState::Locked) {
		aimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (!InPawn) return;

	auto tank = Cast<ATank>(InPawn);
	if (!ensure(tank)) { return; }
	tank->OnTankDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);

}

APawn* ATankAIController::getPlayerTank() const {
    auto pc = GetWorld()->GetFirstPlayerController();
    return pc->GetPawn();
}

void ATankAIController::OnTankDeath()
{
	if (!GetPawn()) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}
