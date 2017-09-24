// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"


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
    aimingComponent->Fire();
}

APawn* ATankAIController::getPlayerTank() const {
    auto pc = GetWorld()->GetFirstPlayerController();
    return pc->GetPawn();
}
