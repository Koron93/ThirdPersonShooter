// Fill out your copyright notice in the Description page of Project Settings.


#include "Rifle.h"

URifle::URifle()
{
	this->Name = "Hi-Carb MK2";

	this->FlavorText = "One Button for you'r problems to go away";

	this->Type = EItemType::Weapon;

	this->Mesh= LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Fab/Sci-Fi_Gun/sci_fi_gun.sci_fi_gun"));
	if (!this->Mesh)UE_LOG(LogTemp, Error, TEXT("Failed to load mesh for URifle!"));

}

URifle::~URifle()
{

}

void URifle::UseItem()
{

}