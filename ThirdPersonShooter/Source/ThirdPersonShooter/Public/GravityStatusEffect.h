// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StatusEffect.h"
#include "GravityStatusEffect.generated.h"

class UCharacterMovementComponent;

UCLASS()
class THIRDPERSONSHOOTER_API UGravityStatusEffect : public UStatusEffect
{
	GENERATED_BODY()

public:
	UGravityStatusEffect();

	virtual void UpdateEffect(float deltaTime, UStatusEffect*& effect) override;

	virtual void StartEffect() override;

private:
	~UGravityStatusEffect();

protected:
	UPROPERTY(BlueprintReadWrite, Category = "Gravity")
	float SlowAmount;

	UPROPERTY(BlueprintReadWrite, Category = "Gravity")
	UCharacterMovementComponent* MovementComponent = nullptr;
	
};
