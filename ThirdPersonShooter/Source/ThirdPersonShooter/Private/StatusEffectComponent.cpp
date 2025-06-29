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
	FName effect = ActiveEffects[i]->EffectName;
	ActiveEffects.RemoveAt(i);

	return effect;
}

FName UStatusEffectComponent::AddEffect(UStatusEffect* effect)
{
	ActiveEffects.Add(effect);

	return effect->EffectName;
}