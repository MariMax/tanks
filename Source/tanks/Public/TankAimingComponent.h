// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

    void aimAt(const FVector&, float);
    
    void SetBarrelReference(UTankBarrel* barrelReference);
    void SetTurretReference(UTankTurret* turretReference);

private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    void moveBarrelTowardsAimDirrection(const FVector&);

};
