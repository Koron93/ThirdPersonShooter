// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffectComponent.h"
#include "StatusEffect.h"

// Sets default values for this component's properties
UStatusEffectComponent::UStatusEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatusEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatusEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FName UStatusEffectComponent::RemoveEffect(int i)
{
	FName effect = ActiveEffects[i].EffectName;
	ActiveEffects.RemoveAt(i);

	return effect;
}

FName UStatusEffectComponent::AddEffect(FStatusEffect effect)
{
	ActiveEffects.Add(effect);

	return effect.EffectName;
}

void UStatusEffectComponent::StatusUpdate(float deltaTime, TArray<int32>& DamageAmount, TArray<EDamageTypeEnum>& DamageType, bool& canMove, bool& isBuff)
{
	TArray<int32> OutDamage;
	TArray<EDamageTypeEnum> OutType;
	bool bOutCanMove = true;
	bool bOutIsBuff = false;

	for (int i = 0; i < ActiveEffects.Num(); i++)
	{

		if (ActiveEffects[i].DamageOverDuration > 0)
		{
			float DamagePerSecond = ActiveEffects[i].DamageOverDuration / ActiveEffects[i].Duration;

			float DamageFromThis = DamagePerSecond * deltaTime;

			EDamageTypeEnum damageType = ActiveEffects[i].DamageType;
			int32 Damage = FMath::RoundToInt32(DamageFromThis);

			OutDamage.Add(Damage);
			OutType.Add(damageType);
		}

		if (ActiveEffects[i].bCanMove)
		{
			bOutCanMove = false;
		}

		if (ActiveEffects[i].bIsBuff)
		{
			bOutIsBuff = false;
		}

		ActiveEffects[i].CountDown -= deltaTime;

		if (ActiveEffects[i].CountDown < 0)
		{
			ActiveEffects.RemoveAt(i);
		}
	}

	DamageAmount = OutDamage;
	DamageType = OutType;
	canMove = bOutCanMove;
	isBuff = bOutIsBuff;
}