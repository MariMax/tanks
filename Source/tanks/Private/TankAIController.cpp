// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"


void ATankAIController::initOwnTank(){
    auto posessedTank = GetControlledTank();
    if (!posessedTank){
        UE_LOG(LogTemp, Error, TEXT("ATankAIController: tank is not posessed"));
    } else {
        ownTank = posessedTank;
        UE_LOG(LogTemp, Warning, TEXT("ATankAIController: tank %s"), *posessedTank->GetName());
    }
}

void ATankAIController::BeginPlay() {
    Super::BeginPlay();
    world = GetWorld();
    initOwnTank();
    auto playerTank = GetPlayerTank();
    if(!playerTank){
        UE_LOG(LogTemp, Error, TEXT("ATankAIController: player not found"));
    } else {
        UE_LOG(LogTemp, Warning, TEXT("ATankAIController: player's tank %s"), *playerTank->GetName());
    }
}

ATank* ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
    auto pc = world->GetFirstPlayerController();
    auto playerPawn = pc->GetPawnOrSpectator();
    if (!playerPawn) return nullptr;
    return Cast<ATank>(playerPawn);
}


ATankAIController::~ATankAIController(){
    delete world;
    delete ownTank;
}
