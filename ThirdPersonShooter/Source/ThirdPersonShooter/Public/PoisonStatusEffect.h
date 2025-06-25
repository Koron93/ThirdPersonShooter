// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatusEffect.h"
#include "PoisonStatusEffect.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPoisonDelegate, int32, Damage);

UCLASS()
class THIRDPERSONSHOOTER_API UPoisonStatusEffect : public UStatusEffect
{
	GENERATED_BODY()

public:
	UPoisonStatusEffect();

	virtual void UpdateEffect(float deltaTime, UStatusEffect*& effect) override;

	UPROPERTY(BlueprintAssignable, Category = "Poison")
	FPoisonDelegate OnPoisonApplied;

private:
	float TickAccumulator;

	~UPoisonStatusEffect();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Poison")
	int32 DamageOverTime;

	UPROPERTY(BlueprintReadWrite, Category = "Poison")
	int32 DamagePerUpdate;

	UPROPERTY(BlueprintReadWrite, Category = "Poison")
	float DamageTickRate;
};
