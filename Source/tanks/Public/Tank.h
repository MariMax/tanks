// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class UTankAimingComponent;

UCLASS()
class TANKS_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();
    
    void aimAt(const FVector&) const;
    
    UFUNCTION(BlueprintCallable, Category="Setup")
    void SetBarrelReference(UTankBarrel* barrelReference);

protected:
    UTankAimingComponent* TankAimingComponent = nullptr;

public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Fire")
    float launchSpeed = 4000.f;
	
	
};
