// Fill out your copyright notice in the Description page of Project Settings.


#include "PoisonStatusEffect.h"

UPoisonStatusEffect::UPoisonStatusEffect()
{
	EffectName = "Poison";
	Duration = 5.0f;
	CountDown = Duration;
	DamageOverTime = 15.0f;
	DamageTickRate = 1.0f;
	TickAccumulator = 0;
	DamagePerUpdate = FMath::RoundToInt32(DamageOverTime / Duration);
}

UPoisonStatusEffect::~UPoisonStatusEffect()
{

}

void UPoisonStatusEffect::UpdateEffect(float deltaTime, UStatusEffect*& effect)
{
	CountDown -= deltaTime;
	effect = nullptr;
	TickAccumulator += deltaTime;

	if (TickAccumulator >= DamageTickRate)
	{
		TickAccumulator = 0.0f;
		OnPoisonApplied.Broadcast(DamagePerUpdate);
	}

	if (CountDown <= 0)
	{
		effect = this;
	}
}