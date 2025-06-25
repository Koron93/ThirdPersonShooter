// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatusEffect.generated.h"

/**
 */

UCLASS(Blueprintable, Abstract)
class THIRDPERSONSHOOTER_API UStatusEffect : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, Category = "Status Effect")
	FName EffectName;

	UPROPERTY(BlueprintReadWrite, Category = "Status Effect")
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effect")
	float CountDown;

	UPROPERTY(BlueprintReadWrite, Category = "Status Effect")
	bool bIsBuff;

	UStatusEffect();

	virtual ~UStatusEffect() override;

protected:
	UFUNCTION(BlueprintCallable, Category = "Status Effect")
	virtual void UpdateEffect(float deltaTime, UStatusEffect*& effect);
};
