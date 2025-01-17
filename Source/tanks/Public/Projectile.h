// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystemComponent;
class UStaticMeshComponent;
class URadialForceComponent;

UCLASS()
class TANKS_API AProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();

	void launchProjectile(float);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void SampleTimerExpired();

	UProjectileMovementComponent* projectileMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category="Setup")
	UParticleSystemComponent* Blast = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UParticleSystemComponent* HitExplosion = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent* StaticMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	URadialForceComponent* ForceImpulse = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	int32 DestroyDelay = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float Damage = 20.f;
};
