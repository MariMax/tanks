// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack(){
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    auto sideSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
    auto correctionAcceleration = -1 * sideSpeed / DeltaTime * GetRightVector();
    auto rootComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto mass = rootComponent->GetMass();
    auto correctionForce = mass * correctionAcceleration / 2;//because there is 2 tracks
    rootComponent->AddForce(correctionForce);
}

void UTankTrack::Throttle(float speed) {
    speed = FMath::Clamp<float>(speed, -1.f, 1.f);
    
    auto appliedForce = GetForwardVector() * speed * MaxTrackDrivingForce;
    auto forceLocation = GetComponentLocation();
    auto tankRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    
    tankRootComponent->AddForceAtLocation(appliedForce, forceLocation);
}
