// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None        UMETA(DisplayName = "None"),
	Weapon      UMETA(DisplayName = "Weapon"),
	Armor       UMETA(DisplayName = "Armor"),
	Grenade  UMETA(DisplayName = "Grenade"),
	Stimulant UMETA(DisplayName = "Stimulant")
};

class THIRDPERSONSHOOTER_API ItemBase
{
public:
	ItemBase();

	~ItemBase();

	EItemType Type;
};
