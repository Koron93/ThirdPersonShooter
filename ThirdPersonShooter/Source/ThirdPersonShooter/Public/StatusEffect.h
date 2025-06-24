// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTypeEnum.h"
#include "StatusEffect.generated.h"

/**
 */

USTRUCT(BlueprintType)
struct THIRDPERSONSHOOTER_API FStatusEffect
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	FName EffectName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	EDamageTypeEnum DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	float CountDown;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	bool bIsBuff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	int32 DamageOverDuration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	bool bCanMove;

	FStatusEffect(): EffectName(NAME_None), Duration(0.0f), CountDown(0.0f), bIsBuff(true), DamageOverDuration(0), bCanMove(true) {}

	~FStatusEffect(){}
};
