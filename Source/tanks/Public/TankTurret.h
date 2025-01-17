// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKS_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
    void Rotate(float);

private:
    UPROPERTY(EditDefaultsOnly, Category=Setup)
    float maxDegreesPerSecond = 20.f;
	
};
