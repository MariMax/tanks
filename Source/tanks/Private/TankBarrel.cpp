// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


void UTankBarrel::Elevate(float relativeSpeed) {
    relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
    auto elevationChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    
    auto newElevation = RelativeRotation.Pitch + elevationChange;
    newElevation = FMath::Clamp<float>(newElevation, minElevationDegrees, maxElevationDegrees);
    
    SetRelativeRotation(FRotator(newElevation, 0, 0));
}

