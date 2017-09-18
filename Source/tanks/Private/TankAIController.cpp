// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"


void ATankAIController::initOwnTank(){
    auto posessedTank = getControlledTank();
    if (!posessedTank){
        UE_LOG(LogTemp, Error, TEXT("ATankAIController: tank is not posessed"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("ATankAIController: tank %s"), *posessedTank->GetName());
    }
}

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
    initOwnTank();
    auto playerTank = getPlayerTank();
    if(!playerTank){
        UE_LOG(LogTemp, Error, TEXT("ATankAIController: player not found"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("ATankAIController: player's tank %s"), *playerTank->GetName());
    }
}

void ATankAIController::Tick(float deltaTime) {
    Super::Tick(deltaTime);
    
    auto playerTank = getPlayerTank();
    auto ownTank = getControlledTank();
    if (!playerTank || !ownTank) return;
    auto playerLocation = playerTank->GetActorLocation();
    ownTank->aimAt(playerLocation);
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
