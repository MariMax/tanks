// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::Throttle(float speed) {
    speed = FMath::Clamp<float>(speed, -1.f, 1.f);
    
    auto appliedForce = GetForwardVector() * speed * MaxTrackDrivingForce;
    auto forceLocation = GetComponentLocation();
    auto tankRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    
    tankRootComponent->AddForceAtLocation(appliedForce, forceLocation);
}
