// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory.h"

// Sets default values for this component's properties
UInventory::UInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	WeaponSwitch = 0;
	// ...
}


// Called when the game starts
void UInventory::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}

void UInventory::AddItem(UItemBase* itemToAdd, UItemBase*& itemthatsAdded)
{
	if (itemToAdd != nullptr) {
		itemthatsAdded = itemToAdd;
		_Inventory.Add(itemToAdd);
	}
}

void UInventory::RemoveItem(UItemBase* itemToRemove)
{
	if (_Inventory.Contains(itemToRemove))
	{
		_Inventory.Remove(itemToRemove);
		itemToRemove->ConditionalBeginDestroy();
	}
}

bool UInventory::EquipItem(UItemBase* itemToEquip, int i)
{
	UItemBase* ItemBeingMoved;
	if (i < 0 || i > 10)
	{
		return false;
	}
	else if (i >= 8 && i <= 10)
	{
		if (i == 8)
		{
			ItemBeingMoved = MainWeapon;
			MainWeapon = itemToEquip;
			_Inventory.Remove(itemToEquip);
			_Inventory.Add(ItemBeingMoved);

			return true;
		}
		else if(i == 10)
		{
			ItemBeingMoved = SideArm;
			SideArm = itemToEquip;
			_Inventory.Remove(itemToEquip);
			_Inventory.Add(ItemBeingMoved);

			return true;
		}
		else
		{
			ItemBeingMoved = Armor;
			Armor = itemToEquip;
			_Inventory.Remove(itemToEquip);
			_Inventory.Add(ItemBeingMoved);

			return true;
		}
	}

	int y = i;

	if (ItemSlots[y] == nullptr) y++;
	else if (ItemSlots[y] == nullptr) y++;
	else if (ItemSlots[y] == nullptr) y++;
	else if (ItemSlots[y] == nullptr) return false;

	ItemSlots[y] = itemToEquip;

	return true;
}

UItemBase* UInventory::UseWeapon()
{
	switch (WeaponSwitch)
	{
	case 1:
	{
		 return MainWeapon;
	}
	case 2:
	{
		return SideArm;
	}
	default:
	{
		return nullptr;
	}
	}
}

UItemBase* UInventory::UseArmor()
{
	return Armor;
}

UItemBase* UInventory::UseStim()
{
	if (ItemSlots[0] != nullptr) return ItemSlots[0];
	else if (ItemSlots[1] != nullptr) return ItemSlots[1];
	else if (ItemSlots[2] != nullptr) return ItemSlots[2];
	else if (ItemSlots[3] != nullptr) return ItemSlots[3];

	return nullptr;
}

UItemBase* UInventory::UseGrenade()
{
	if (ItemSlots[0] != nullptr) return ItemSlots[4];
	else if (ItemSlots[1] != nullptr) return ItemSlots[5];
	else if (ItemSlots[2] != nullptr) return ItemSlots[6];
	else if (ItemSlots[3] != nullptr) return ItemSlots[7];

	return nullptr;
}