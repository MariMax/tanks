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
    auto ownTank = getControlledTank();
    if (!ensure(playerTank && ownTank)) return;
    
    auto playerLocation = playerTank->GetActorLocation();
    
    MoveToActor(playerTank, HowFarAwayICanStopMpvingTowardsTheGoal);
    
    auto aimingComponent = ownTank->FindComponentByClass<UTankAimingComponent>();
    if(!ensure(aimingComponent)) {return;}
    
    aimingComponent->aimAt(playerLocation);
    aimingComponent->Fire();
}

ATank* ATankAIController::getControlledTank() const {
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::getPlayerTank() const {
    auto pc = GetWorld()->GetFirstPlayerController();
    auto playerPawn = pc->GetPawnOrSpectator();
    if (!playerPawn) return nullptr;
    return Cast<ATank>(playerPawn);
}
