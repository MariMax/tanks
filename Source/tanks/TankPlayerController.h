// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "public/Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
    
    ATank* ownTank;
	
    ATank* GetControlledTank() const;
    void aimTowardsCrosshair();
    
    virtual void BeginPlay() override;
    virtual void Tick(float) override;
	
    ~ATankPlayerController();
};
