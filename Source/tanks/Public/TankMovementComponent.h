// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * component responsible for tank movement
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
    //initiliaze tracks on movement component
    UFUNCTION(BlueprintCallable, Category="Setup")
    void InitTracks(UTankTrack* lt, UTankTrack* rt);
    
    // Accepts value from -1 to +1 to move tank back and forth
	UFUNCTION(BlueprintCallable, Category="Action")
    void IntendMoveForward(float Throw);
    
    UFUNCTION(BlueprintCallable, Category="Action")
    void IntendRotate(float Throw);
	
private:
    void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

    UTankTrack* LeftTrack = nullptr;
    UTankTrack* RightRtack = nullptr;
};
