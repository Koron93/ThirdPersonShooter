// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageTypeEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EDamageTypeEnum : uint8
{
	Bullet,
	Gravity,
	Blunt,
	Explosive,
	Poison,
	Unknown
};
