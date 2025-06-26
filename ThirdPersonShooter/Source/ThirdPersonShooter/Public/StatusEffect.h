// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatusEffect.generated.h"

/**
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStatusApplied);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStatusRemoved);

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

	UPROPERTY(BlueprintReadWrite, Category = "Status Effect")
	AActor* AffectedTarget;

	UPROPERTY(BlueprintAssignable, Category = "Status Effect")
	FStatusApplied StatusApplied;

	UPROPERTY(BlueprintAssignable, Category = "Status Effect")
	FStatusRemoved StatusDismantled;

	UFUNCTION(BlueprintCallable, Category = "Status Effect")
	void InitializeEffect(AActor* TargetActor);

	UFUNCTION(BlueprintImplementableEvent, Category = "Status Effect")
	void OnEffectInitialized();

	UStatusEffect();

	virtual ~UStatusEffect() override;

	UFUNCTION(BlueprintCallable, Category = "Status Effect")
	virtual void StartEffect();

protected:
	UFUNCTION(BlueprintCallable, Category = "Status Effect")
	virtual void UpdateEffect(float deltaTime, UStatusEffect*& effect);
};
