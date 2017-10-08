// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class TANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
    virtual void BeginPlay() override;
	void SetPawn(APawn * InPawn) override;
	UFUNCTION()
	void OnTankDestroyed();
	virtual void Tick(float) override;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="CrossHair Position")
    float crossHairXPosition = .5f;
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="CrossHair Position")
    float crossHairYPosition = .5f;
    UPROPERTY(EditDefaultsOnly, Category="Weapon Settings")
    float maxHitDistance = 10000.f;

protected:
    UFUNCTION(BlueprintImplementableEvent, Category="Setup")
    void AimingComponentFound(UTankAimingComponent* AimingComponentRef);
    
private:
    FVector2D getAimPointScreenLocation(int32, int32) const;
    void aimTowardsCrosshair();
    
    bool getSightRayHitLoaction(FVector&) const;
    bool getLookDirection(const FVector2D&, FVector&) const;
    bool getVectorHitLocation(const FVector&, FVector&) const;
};
