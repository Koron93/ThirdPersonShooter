// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "Rifle.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API URifle : public UItemBase
{
	GENERATED_BODY()

public:
	URifle();

	virtual ~URifle();

	virtual void UseItem() override;

private:
	int32 Damage;

	int32 FireRate;
	
};
