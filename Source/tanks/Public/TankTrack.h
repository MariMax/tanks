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

public:
	UFUNCTION(BlueprintCallable)
    void Throttle(float speed);
    
private:
    UTankTrack();
	virtual void BeginPlay() override;
	void DriveTrack(float);
	
	float CurrentThrottle = 0;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void ApplySideForce();
    //Max force per track in newtons
    UPROPERTY(EditDefaultsOnly)
    float MaxTrackDrivingForce = 20000000.f;
};
