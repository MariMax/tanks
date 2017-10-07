// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 damage = FMath::Clamp(FMath::RoundToInt(DamageAmount), 0, CurrentHealth);
	CurrentHealth -= damage;
	return damage;
}

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}
