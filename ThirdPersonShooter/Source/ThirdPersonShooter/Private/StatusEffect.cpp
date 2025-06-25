// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffect.h"

UStatusEffect::UStatusEffect()
{
	EffectName = "None";
	Duration = 0.0f;
	bIsBuff = false;
	CountDown = Duration;
}

UStatusEffect::~UStatusEffect()
{

}

void UStatusEffect::UpdateEffect(float deltaTime, UStatusEffect*& effect)
{

}