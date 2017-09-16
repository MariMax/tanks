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
    
    FVector hitLocation;
    
    if (getSightRayHitLoaction(hitLocation)){
        
    }
}

bool ATankPlayerController::getSightRayHitLoaction(FVector& out_hitLocation) const {
    int32 viewportSizeX, viewportSizeY;
    GetViewportSize(viewportSizeX, viewportSizeY);
    auto crossHairPositionScreenLocation = getAimPointScreenLocation(viewportSizeX, viewportSizeY);
    
    
    return false;
}

FVector2D ATankPlayerController::getAimPointScreenLocation(int32 viewportSizeX, int32 viewportSizeY) const {
    return FVector2D(viewportSizeX * crossHairXPosition,viewportSizeY * crossHairYPosition);
}














ATankPlayerController::~ATankPlayerController() {
    delete ownTank;
}
