// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class TANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
    void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    
    ATank* getControlledTank() const;
    void initOwnTank();
    
    ATank* getPlayerTank() const;
    
    UPROPERTY(EditDefaultsOnly, Category="Setup")
    float HowFarAwayICanStopMpvingTowardsTheGoal = 2000;
	
};
