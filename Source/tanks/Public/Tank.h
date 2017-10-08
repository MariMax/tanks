// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

UCLASS()
class TANKS_API ATank : public APawn
{
	GENERATED_BODY()

	void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	UFUNCTION(BlueprintPure)
	float GetHealthPersentage() const;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	int32 CurrentHealth;


public:
	FTankDelegate OnTankDeath;
	// Sets default values for this pawn's properties
	ATank();
};
