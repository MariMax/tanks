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
    if (FPlatformTime::Seconds() - LastFireTime < ReloadTimeInSeconds) {
        CrosshairState = ECrosshairState::Reloading;
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
        FVector aimDirrection = OutLaunchVelocity.GetSafeNormal();
        moveBarrelTowardsAimDirrection(aimDirrection);
    }
}

void UTankAimingComponent::Fire() {
    if (CrosshairState == ECrosshairState::Reloading) {return;}
    if (!ensure(Barrel) || !ensure(ProjectileBlueprint)) {return;}
    
    //spawn projectile at the socket location
    auto location = Barrel->GetSocketLocation(FName("Projectile"));
    auto rotation = Barrel->GetSocketRotation(FName("Projectile"));
    auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, location, rotation);
    LastFireTime = FPlatformTime::Seconds();
    projectile->launchProjectile(LaunchSpeed);

}

void UTankAimingComponent::moveBarrelTowardsAimDirrection(const FVector& aimDirrection) {
    if (!Barrel || !Turret) return;
    auto currentRotation = Barrel->GetForwardVector().Rotation();
    auto aimRotation = aimDirrection.Rotation();
    auto diff = aimRotation - currentRotation;
    
    Barrel->Elevate(diff.Pitch);
    Turret->Rotate(diff.Yaw);
}
