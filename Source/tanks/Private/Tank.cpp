// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    
    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Tank Aiming Component"));

}

void ATank::SetBarrelReference(UTankBarrel* barrelReference){
    TankAimingComponent->SetBarrelReference(barrelReference);
}

void ATank::SetTurretReference(UTankTurret* turretReference){
    TankAimingComponent->SetTurretReference(turretReference);
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::aimAt(const FVector& hitLocation) const {
    TankAimingComponent->aimAt(hitLocation, launchSpeed);
}

void ATank::Fire(){
    UE_LOG(LogTemp, Warning, TEXT("Fire"));
}

