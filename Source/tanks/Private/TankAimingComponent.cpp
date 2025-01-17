// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::InitAimingComponent(UTankBarrel* barrel, UTankTurret* turret){
    Turret = turret;
    Barrel = barrel;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (Ammo <= 0) {
		CrosshairState = ECrosshairState::Empty;
		return;
	}
    if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds) {
        CrosshairState = ECrosshairState::Reloading;
        return;
    }
	if (Barrel && Barrel->GetForwardVector().Equals(AimDirection, 0.01)) {
		CrosshairState = ECrosshairState::Locked;
		return;
	}
    CrosshairState = ECrosshairState::Ready;
}

void UTankAimingComponent::aimAt(const FVector& hitLocation){
    if (!ensure(Barrel) || !ensure(Turret)) return;
    FVector OutLaunchVelocity;
    FCollisionResponseParams collisionResponseParams(ECollisionResponse::ECR_Block);
    
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
                                                                        this,
                                                                        OutLaunchVelocity,
                                                                        Barrel->GetSocketLocation(FName("Projectile")),
                                                                        hitLocation,
                                                                        LaunchSpeed,
                                                                        false,
                                                                        1.f,
                                                                        0.f,
                                                                        ESuggestProjVelocityTraceOption::Type::DoNotTrace
                                                                        );
    
    if (bHaveAimSolution){
        AimDirection = OutLaunchVelocity.GetSafeNormal();
        moveBarrelTowardsAimDirrection();
    }
}

void UTankAimingComponent::Fire() {
    if (CrosshairState == ECrosshairState::Reloading || CrosshairState == ECrosshairState::Empty) {return;}
    if (!ensure(Barrel) || !ensure(ProjectileBlueprint)) {return;}
	Ammo--;
    //spawn projectile at the socket location
    auto location = Barrel->GetSocketLocation(FName("Projectile"));
    auto rotation = Barrel->GetSocketRotation(FName("Projectile"));
    auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, location, rotation);
    LastFireTime = FPlatformTime::Seconds();
    projectile->launchProjectile(LaunchSpeed);
}

ECrosshairState UTankAimingComponent::GetCrosshairState() const
{
	return CrosshairState;
}

int32 UTankAimingComponent::GetAmmo() const
{
	return Ammo;
}

void UTankAimingComponent::moveBarrelTowardsAimDirrection() {
    if (!Barrel || !Turret) return;
    auto currentRotation = Barrel->GetForwardVector().Rotation();
    auto aimRotation = AimDirection.Rotation();
    auto diff = aimRotation - currentRotation;
    
    Barrel->Elevate(diff.Pitch);
	if (FMath::Abs(diff.Yaw) > 180) diff.Yaw = 180 - diff.Yaw;
    Turret->Rotate(diff.Yaw);
}
