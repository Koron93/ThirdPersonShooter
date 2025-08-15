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
	HealthComponent = nullptr;
	TotalTime = 0;
	TimeStacks.Add(Duration);
}

UPoisonStatusEffect::~UPoisonStatusEffect()
{
	StatusDismantled.Clear();
	StatusApplied.Clear();
}

void UPoisonStatusEffect::UpdateEffect(float deltaTime, UStatusEffect*& effect)
{

	for (float& stack : TimeStacks)
	{
		stack -= deltaTime;
	}

	CountDown = TimeStacks.Last();
	effect = nullptr;
	TickAccumulator += deltaTime;
	TotalTime += deltaTime;

	if (TickAccumulator >= DamageTickRate)
	{
		DamagePerUpdate = FMath::RoundToInt32(DamageOverTime / Duration);
		DamagePerUpdate = DamagePerUpdate * TimeStacks.Num();
		TickAccumulator = 0.0f;

		StatusApplied.Broadcast();

		if (TimeStacks[0] <= 0) TimeStacks.RemoveAt(0);
	}

	if (CountDown <= 0)
	{
		StatusDismantled.Broadcast();

		effect = this;
	}
}

void UPoisonStatusEffect::StartEffect()
{

}