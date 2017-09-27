// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay() {
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack(CurrentThrottle);
	ApplySideForce();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySideForce()
{
	auto sideSpeed = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto correctionAcceleration = -1 * sideSpeed / DeltaTime * GetRightVector();
	auto rootComponent = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto mass = rootComponent->GetMass();
	auto correctionForce = mass * correctionAcceleration / 2;//because there is 2 tracks
	rootComponent->AddForce(correctionForce);
}

void UTankTrack::Throttle(float speed) {
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle+speed, -1.f, 1.f);
}

void UTankTrack::DriveTrack(float speed) {
	auto appliedForce = GetForwardVector() * speed * MaxTrackDrivingForce;
	auto forceLocation = GetComponentLocation();
	auto tankRootComponent = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankRootComponent->AddForceAtLocation(appliedForce, forceLocation);
}
