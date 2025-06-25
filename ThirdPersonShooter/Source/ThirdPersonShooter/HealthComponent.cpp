// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Health = MaxHealth;
	Shield = MaxShield;
	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(int32 Damage, EDamageTypeEnum damagetype)
{
	int32 DamageToApplie = 0;

	switch (damagetype)
	{
	case::EDamageTypeEnum::Bullet:
	{
		break;
	}
	case::EDamageTypeEnum::Blunt:
	{
		break;
	}
	case::EDamageTypeEnum::Explosive:
	{
		break;
	}
	case::EDamageTypeEnum::Gravity:
	{
		break;
	}
	default:
	{
		DamageToApplie = Damage;
		break;
	}
	}
	int32 newHealth = FMath::Clamp(Health - DamageToApplie, 0, MaxHealth);
	UHealthComponent::Health = newHealth;

	if (Health <= 0)
	{
		DeathEvent.Broadcast();
	}

}

void UHealthComponent::TakeShieldDamage(int32 damage, EDamageTypeEnum damagetype)
{
	int32 DamageToApplie = 0;

	switch (damagetype)
	{
	case::EDamageTypeEnum::Bullet:
	{
		break;
	}
	case::EDamageTypeEnum::Blunt:
	{
		break;
	}
	case::EDamageTypeEnum::Explosive:
	{
		break;
	}
	case::EDamageTypeEnum::Gravity:
	{
		break;
	}
	default:
	{
		DamageToApplie = damage;
		break;
	}
	}

	UHealthComponent::Shield -= DamageToApplie;

	if(Shield < 0)
	{
		TakeDamage(Shield, damagetype); 
		Shield = 0;
		bHasShield = false;
	}
	else if (Shield > 0 && damage < 0)
	{
		bHasShield = true;
		int32 newShield = FMath::Clamp(Shield - damage, 0, MaxShield);
		Shield = newShield;
	}
}