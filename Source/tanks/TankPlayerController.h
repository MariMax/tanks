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
public:
    virtual void BeginPlay() override;
    virtual void Tick(float) override;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="CrossHair Position")
    float crossHairXPosition = .5f;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="CrossHair Position")
    float crossHairYPosition = .5f;

private:
    ATank* ownTank;
	
    ATank* GetControlledTank() const;
    FVector2D getAimPointScreenLocation(int32, int32) const;
    void aimTowardsCrosshair();
    
    bool getSightRayHitLoaction(FVector&) const;
	
    ~ATankPlayerController();
};
