// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class UStaticMeshComponent;

UCLASS()
class TANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

	// Called every frame
	virtual void Tick(float) override;

	void launchProjectile(float);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UProjectileMovementComponent* projectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category="Setup")
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent* StaticMesh = nullptr;
};
