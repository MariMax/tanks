// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include <GameFramework/ProjectileMovementComponent.h>
#include <Particles/ParticleSystemComponent.h>


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateAbstractDefaultSubobject<UStaticMeshComponent>(FName("Static Mesh"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetNotifyRigidBodyCollision(true);
	StaticMesh->SetVisibility(false);

	Blast = CreateAbstractDefaultSubobject<UParticleSystemComponent>(FName("Projectile smoke tail"));
	Blast->AttachTo(RootComponent);// , FAttachmentTransformRules::KeepRelativeTransform);

	HitExplosion = CreateAbstractDefaultSubobject<UParticleSystemComponent>(FName("Hit Explosion"));
	HitExplosion->AttachTo(RootComponent);//, FAttachmentTransformRules::KeepRelativeTransform);
	HitExplosion->bAutoActivate = false;

	projectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("projectile movement"));
	projectileMovementComponent->bAutoActivate = false;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	Blast->Deactivate();
	HitExplosion->Activate();
}

void AProjectile::launchProjectile(float speed)
{
	projectileMovementComponent->SetVelocityInLocalSpace(FVector::ForwardVector * speed);
	projectileMovementComponent->Activate();
}

