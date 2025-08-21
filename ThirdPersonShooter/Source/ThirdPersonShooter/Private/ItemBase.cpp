// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

UItemBase::UItemBase()
{
	Type = EItemType::None;

	Mesh = nullptr;

	Name = "item";

	FlavorText = "base item";
}

UItemBase::~UItemBase()
{
	Type = EItemType::None;

	Mesh = nullptr;

	Name = "item";

	FlavorText = "base item";
}

void UItemBase::UseItem()
{

}
