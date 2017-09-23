// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TANKS_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable)
    void Throttle(float speed);
    
    //Max forcw per track in newtons
    UPROPERTY(EditDefaultsOnly)
    float MaxTrackDrivingForce = 400000.f;
	
	
};
