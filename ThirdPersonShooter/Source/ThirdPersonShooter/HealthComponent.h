// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageTypeEnum.h"
#include "HealthComponent.generated.h"

//UENUM(BlueprintType)
//enum class ADamageType : uint8
//{
//	Bullet,
//	Gravity,
//	Blunt,
//	Explosive,
//	Unknown
//};


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONSHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UPROPERTY(Category = "Health", BlueprintReadWrite)
	int32 MaxHealth = 100;

	UPROPERTY(Category = "Health", BlueprintReadWrite)
	int32 MaxShield = 100;

	UPROPERTY(Category = "Health", BlueprintReadWrite)
	int32 Health;

	UPROPERTY(Category = "Health", BlueprintReadWrite)
	int32 Shield;

	UPROPERTY(Category = "Health", BlueprintReadWrite)
	bool bHasShield = true;

	UPROPERTY(Category = "Health", BlueprintReadWrite)
	bool bIsAlive = true;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(Category = "Health", BlueprintCallable)
	void TakeDamage(int32 damage, EDamageTypeEnum damagetype);

	UFUNCTION(Category = "Health", BlueprintCallable)
	void TakeShieldDamage(int32 damage, EDamageTypeEnum damagetype);

	UPROPERTY(BlueprintAssignable, Category = "Health")
	FDeathDelegate DeathEvent;
		
};
