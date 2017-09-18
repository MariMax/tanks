// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include <Kismet/GameplayStatics.h>


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* barrelReference) {
    Barrel = barrelReference;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* turretReference) {
    Turret = turretReference;
}


void UTankAimingComponent::aimAt(const FVector& hitLocation, float launchSpeed){
    if (!Barrel || !Turret) return;
    FVector OutLaunchVelocity;
    FCollisionResponseParams collisionResponseParams(ECollisionResponse::ECR_Block);
    
    bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
                                                                        this,
                                                                        OutLaunchVelocity,
                                                                        Barrel->GetSocketLocation(FName("Projectile")),
                                                                        hitLocation,
                                                                        launchSpeed,
                                                                        false,
                                                                        1.f,
                                                                        0.f,
                                                                        ESuggestProjVelocityTraceOption::Type::DoNotTrace
                                                                        );
    
    if (bHaveAimSolution){
        FVector aimDirrection = OutLaunchVelocity.GetSafeNormal();
        moveBarrelTowardsAimDirrection(aimDirrection);
        
//        auto Time = GetWorld()->GetTimeSeconds();
//        UE_LOG(LogTemp, Warning, TEXT("%f: +"), Time);

    }
//    else {
//        auto Time = GetWorld()->GetTimeSeconds();
//        UE_LOG(LogTemp, Warning, TEXT("%f: +"), Time);
//
//    }

}

void UTankAimingComponent::moveBarrelTowardsAimDirrection(const FVector& aimDirrection) {
    if (!Barrel || !Turret) return;
    auto currentRotation = Barrel->GetForwardVector().Rotation();
    auto aimRotation = aimDirrection.Rotation();
    auto diff = aimRotation - currentRotation;
    
    
    Barrel->Elevate(diff.Pitch);
    Turret->Rotate(diff.Yaw);
}



