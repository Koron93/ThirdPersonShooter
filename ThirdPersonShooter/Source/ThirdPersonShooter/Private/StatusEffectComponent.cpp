// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusEffectComponent.h"
#include "StatusEffect.h"

// Sets default values for this component's properties
UStatusEffectComponent::UStatusEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ActiveEffects.Empty();
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
	FName name = ActiveEffects[i]->EffectName;

	ActiveEffects.RemoveAt(i);

	return name;
}

UStatusEffect* UStatusEffectComponent::AddEffect(UStatusEffect* effect)
{
	for (int i = 0; i < ActiveEffects.Num(); i++)
	{
		if (ActiveEffects[i]->EffectName != effect->EffectName) continue;

		return ActiveEffects[i];
	}

	ActiveEffects.Add(effect);
	return effect;
}