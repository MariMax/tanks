// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();
    auto posessedTank = GetControlledTank();
    if (!posessedTank){
        UE_LOG(LogTemp, Error, TEXT("ATankPlayerController: tank is not posessed"));
    } else {
        ownTank = posessedTank;
        UE_LOG(LogTemp, Warning, TEXT("ATankPlayerController: tank %s"), *posessedTank->GetName());
    }
}

void ATankPlayerController::Tick(float deltaTime) {
    Super::Tick(deltaTime);
    aimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::aimTowardsCrosshair(){
    if (!ownTank) return;
}

ATankPlayerController::~ATankPlayerController() {
    delete ownTank;
}
