// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatusEffect.h"
#include "PoisonStatusEffect.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API UPoisonStatusEffect : public UStatusEffect
{
	GENERATED_BODY()

public:
	UPoisonStatusEffect();

	virtual void UpdateEffect(float deltaTime, UStatusEffect*& effect) override;

	virtual void StartEffect() override;

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
