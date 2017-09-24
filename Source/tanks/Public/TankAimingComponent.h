// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class ECrosshairState : uint8 {
    Ready,
    Reloading
};

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
    
protected:
    UPROPERTY(BlueprintReadOnly, Category = "State")
    ECrosshairState CrosshairState = ECrosshairState::Reloading;

private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;
    
    void moveBarrelTowardsAimDirrection(const FVector&);

};
