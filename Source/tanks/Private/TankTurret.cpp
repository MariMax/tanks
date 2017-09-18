// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::Rotate(float relativeSpeed) {
    relativeSpeed = FMath::Clamp<float>(relativeSpeed, -1, 1);
    auto degreeChange = relativeSpeed * maxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    
    auto newDegree = RelativeRotation.Yaw + degreeChange;
    SetRelativeRotation(FRotator(0, newDegree, 0));
}


