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

	UFUNCTION(BlueprintCallable, Category = "UseItem")
	void AddItem(UItemBase* itemToAdd, UItemBase*& itemthatsAdded);

	UFUNCTION(BlueprintCallable, Category = "UseItem")
	void RemoveItem(UItemBase* itemToRemove);

	UFUNCTION(BlueprintCallable, Category = "UseItem")
	bool EquipItem(UItemBase* itemToEquip, int i);

	UFUNCTION(BlueprintCallable, Category = "UseItem")
	UItemBase* UseWeapon();

	UFUNCTION(BlueprintCallable, Category = "UseItem")
	UItemBase* UseArmor();

	UFUNCTION(BlueprintCallable, Category = "UseItem")
	UItemBase* UseStim();

	UFUNCTION(BlueprintCallable, Category = "UseItem")
	UItemBase* UseGrenade();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Items")
	TArray<UItemBase*> _Inventory;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Items")
	TArray<UItemBase*> ItemSlots;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Items")
	UItemBase* MainWeapon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Items")
	UItemBase* Armor;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Items")
	UItemBase* SideArm;

private:
	int WeaponSwitch;
};
