// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "HandGun.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API UHandGun : public UItemBase
{
	GENERATED_BODY()

public:
	UHandGun();

	virtual ~UHandGun();

	virtual void UseItem() override;

private:
	int32 Damage;

	int32 FireRate;

};