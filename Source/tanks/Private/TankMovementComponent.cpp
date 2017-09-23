// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::InitTracks(UTankTrack* lt, UTankTrack* rt) {
    LeftTrack = lt;
    RightRtack = rt;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
    auto speed = FMath::Clamp<float>(Throw, -1.f, 1.f);
    if (!LeftTrack || !RightRtack) return;
    LeftTrack->Throttle(speed);
    RightRtack->Throttle(speed);
}


void UTankMovementComponent::IntendRotate(float Throw) {
    auto speed = FMath::Clamp<float>(Throw, -1.f, 1.f);
    if (!LeftTrack || !RightRtack) return;
    LeftTrack->Throttle(speed);
    RightRtack->Throttle(-speed);
}
