// Fill out your copyright notice in the Description page of Project Settings.


#include "HandGun.h"

UHandGun::UHandGun()
{
	this->Name = "Light weight blaster";

	this->FlavorText = "Can go pewpew";

	this->Type = EItemType::SideArm;

	this->Mesh = LoadObject<UStaticMesh>(nullptr, TEXT("/Game/Fab/Sci-fi_Gun_Venra-46_/sci_fi_gunvenra_46.sci_fi_gunvenra_46"));
	if (!this->Mesh)UE_LOG(LogTemp, Error, TEXT("Failed to load mesh for UHandGun!"));
}

UHandGun::~UHandGun()
{

}

void UHandGun::UseItem()
{

}