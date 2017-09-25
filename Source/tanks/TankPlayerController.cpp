// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) {return;}
    AimingComponentFound(AimingComponent);
}

void ATankPlayerController::Tick(float deltaTime) {
    Super::Tick(deltaTime);
    aimTowardsCrosshair();
}

void ATankPlayerController::aimTowardsCrosshair(){
    if(!GetPawn()) {return;}
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) {return;}
    
    FVector hitLocation;
    
    if (getSightRayHitLoaction(hitLocation)){
        //we can hit something
        AimingComponent->aimAt(hitLocation);
    }
}

bool ATankPlayerController::getSightRayHitLoaction(FVector& out_hitLocation) const {
    int32 viewportSizeX, viewportSizeY;
    GetViewportSize(viewportSizeX, viewportSizeY);
    auto crossHairPositionScreenLocation = getAimPointScreenLocation(viewportSizeX, viewportSizeY);
    
    FVector lookDirection;
    return getLookDirection(crossHairPositionScreenLocation, lookDirection) &&
    getVectorHitLocation(lookDirection, out_hitLocation);
}

FVector2D ATankPlayerController::getAimPointScreenLocation(int32 viewportSizeX, int32 viewportSizeY) const {
    return FVector2D(viewportSizeX * crossHairXPosition,viewportSizeY * crossHairYPosition);
}

bool ATankPlayerController::getLookDirection(const FVector2D& screenLocation, FVector& out_lookDirection) const {
    out_lookDirection = FVector(0);
    FVector cameraLocation;
    return DeprojectScreenPositionToWorld(
                                          screenLocation.X,
                                          screenLocation.Y,
                                          cameraLocation,
                                          out_lookDirection);
}

bool ATankPlayerController::getVectorHitLocation(const FVector& direction, FVector& out_Hit) const {
    auto ownTank = GetPawn();
    if (!ownTank) return false;
    auto tankLocation = PlayerCameraManager->GetCameraLocation();
    FVector end = tankLocation + direction * maxHitDistance;
    
    FCollisionResponseParams collisionResponseParams(ECollisionResponse::ECR_Block);
    FCollisionQueryParams collisionQueryParams(
        FName(TEXT("")),
        false,
        ownTank
    );
    
    FHitResult hitResult;
    
    if(GetWorld()->LineTraceSingleByChannel(
        hitResult,
        tankLocation,
        end,
        ECC_Visibility,
        collisionQueryParams,
        collisionResponseParams
    )) {
        out_Hit = hitResult.Location;
        return true;
    }
    out_Hit = FVector(0);
    return false;
}
