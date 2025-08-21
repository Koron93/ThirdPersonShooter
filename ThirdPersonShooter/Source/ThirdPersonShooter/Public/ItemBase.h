// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.generated.h"

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None        UMETA(DisplayName = "None"),
	Weapon      UMETA(DisplayName = "Weapon"),
	SideArm      UMETA(DisplayName = "SideArm"),
	Armor       UMETA(DisplayName = "Armor"),
	Grenade  UMETA(DisplayName = "Grenade"),
	Stimulant UMETA(DisplayName = "Stimulant")
};

UCLASS(Blueprintable)
class THIRDPERSONSHOOTER_API UItemBase : public UObject
{	
	GENERATED_BODY()

public:
	UItemBase();

	virtual ~UItemBase();

	UPROPERTY()
	EItemType Type;

	UPROPERTY()
	FName Name;

	UPROPERTY()
	FName FlavorText;

	UFUNCTION()
	virtual void UseItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item")
	UStaticMesh* Mesh;
};
