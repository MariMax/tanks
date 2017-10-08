// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) {
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();
	auto AIForwardVector = GetOwner()->GetActorForwardVector();

	auto forwardIntention = FVector::DotProduct(AIForwardIntention, AIForwardVector);
	IntendMoveForward(forwardIntention);
	auto turnIntention = 1 - forwardIntention;
	auto rotation = FVector::CrossProduct(AIForwardIntention, AIForwardVector);
	IntendRotate(rotation.Z);
//    UE_LOG(LogTemp, Warning, TEXT("%s moving to you %f"), *GetOwner()->GetName(), forwardIntention);

}

void UTankMovementComponent::InitTracks(UTankTrack* lt, UTankTrack* rt) {
    LeftTrack = lt;
    RightRtack = rt;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
    auto speed = FMath::Clamp<float>(Throw, -2.f, 2.f);
    if (!LeftTrack || !RightRtack) return;
    LeftTrack->Throttle(speed);
    RightRtack->Throttle(speed);
}


void UTankMovementComponent::IntendRotate(float Throw) {
    auto speed = FMath::Clamp<float>(Throw, -2.f, 2.f);
    if (!LeftTrack || !RightRtack) return;
    LeftTrack->Throttle(speed);
    RightRtack->Throttle(-speed);
}
