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
class UTankAimingComponent;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

    void aimAt(const FVector&);
    
    UFUNCTION(BlueprintCallable, Category="Setup")
    void Fire();
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "State")
    ECrosshairState CrosshairState = ECrosshairState::Ready;
    
    UFUNCTION(BlueprintCallable, Category="Setup")
    void InitAimingComponent(UTankBarrel* barrel, UTankTurret* turret);
    
private:
    UTankBarrel* Barrel = nullptr;
    UTankTurret* Turret = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Fire")
    float ReloadTimEInSeconds = 10;
    
    UPROPERTY(EditDefaultsOnly, Category="Fire")
    float LaunchSpeed = 4000.f;
    
    double LastFireTime = FPlatformTime::Seconds();
    
    UPROPERTY(EditDefaultsOnly, Category="Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;
    
    void moveBarrelTowardsAimDirrection(const FVector&);

};
