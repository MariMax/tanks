// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::Throttle(float speed) {
//    if (FMath::RoundToZero(speed) == 0) return;
    speed = FMath::Clamp<float>(speed, -1.f, 1.f);
    
    auto appliedForce = GetForwardVector() * speed * MaxTrackDrivingForce;
    auto forceLocation = GetComponentLocation();
    
    
    auto time = GetWorld()->GetTimeSeconds();
    auto tankRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    
    tankRootComponent->AddForceAtLocation(appliedForce, forceLocation);
    UE_LOG(LogTemp, Warning, TEXT("%f: %s throttle %f"), time, *GetName(), speed);
}
