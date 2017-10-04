// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetNotifyRigidBodyCollision(true);
	StaticMesh->SetVisibility(false);


	LaunchBlast = CreateAbstractDefaultSubobject<UParticleSystemComponent>(FName("Particle system"));
	LaunchBlast->AttachTo(RootComponent);

	

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("projectile movement"));
	projectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::launchProjectile(float speed)
{
	projectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projectileMovementComponent->Activate();
}

