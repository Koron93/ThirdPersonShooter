// Fill out your copyright notice in the Description page of Project Settings.


#include "GravityStatusEffect.h"

UGravityStatusEffect::UGravityStatusEffect()
{
	EffectName = "Slow";
	Duration = 10.0f;
	CountDown = Duration;
	SlowAmount = 50.0f;
}

UGravityStatusEffect::~UGravityStatusEffect()
{

}

void UGravityStatusEffect::UpdateEffect(float deltaTime, UStatusEffect*& effect)
{
	effect = nullptr;
	CountDown -= deltaTime;

	if (CountDown <= 0)
	{
		effect = this;
	}
}