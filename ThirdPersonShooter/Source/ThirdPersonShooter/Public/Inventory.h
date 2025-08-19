// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ItemBase.h"
#include "Inventory.generated.h"

DECLARE_EVENT(UInventory, UseItem);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class THIRDPERSONSHOOTER_API UInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddItem(ItemBase* itemToAdd);

	void RemoveItem(ItemBase* itemToRemove);

	bool EquipItem(ItemBase* itemToEquip, int i);

	ItemBase* UseWeapon();

	ItemBase* UseSideArm();

	ItemBase* UseArmor();

	ItemBase* UseStim();

	ItemBase* UseGrenade();

private:
	TArray<ItemBase*> _Inventory;

	TArray<ItemBase*> ItemSlots;

	ItemBase* MainWeapon;

	ItemBase* Armor;

	ItemBase* SideArm;
};
