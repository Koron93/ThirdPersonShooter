// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffect.h"

UStatusEffect::UStatusEffect()
{
	EffectName = "None";
	Duration = 0.0f;
	bIsBuff = false;
	CountDown = Duration;
	AffectedTarget = nullptr;
}

UStatusEffect::~UStatusEffect()
{
	EffectName = "None";
	Duration = 0.0f;
	bIsBuff = false;
	CountDown = Duration;
	AffectedTarget = nullptr;
}

void UStatusEffect::UpdateEffect(float deltaTime, UStatusEffect*& effect)
{

}

void UStatusEffect::StartEffect()
{

}

void UStatusEffect::InitializeEffect(AActor* TargetActor)
{
	AffectedTarget = TargetActor;
	OnEffectInitialized();
}
