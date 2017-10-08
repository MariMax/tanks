// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 damage = FMath::Clamp(FMath::RoundToInt(DamageAmount), 0, CurrentHealth);
	CurrentHealth -= damage;
	if (CurrentHealth <= 0) {
		OnTankDeath.Broadcast();
	}
	return damage;
}

float ATank::GetHealthPersentage() const
{
	return 1.0f * CurrentHealth / MaxHealth;
}

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}
