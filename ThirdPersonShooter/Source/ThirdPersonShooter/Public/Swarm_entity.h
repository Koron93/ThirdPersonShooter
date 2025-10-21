// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Swarm_entity.generated.h"

UENUM(BlueprintType)
enum BehaviorState : uint8
{
	Hungry,
	Thirsty,
	Sleepy,
	Patroling
};

UCLASS()
class THIRDPERSONSHOOTER_API ASwarm_entity : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASwarm_entity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<BehaviorState> CurrentState;

	UPROPERTY(BlueprintReadWrite)
	float Hunger;

	UPROPERTY(BlueprintReadWrite)
	float Thirst;

	UPROPERTY(BlueprintReadWrite)
	float Rested;

private:
	UFUNCTION()
	void CalcValues();

	UFUNCTION()
	void HandleTimer();

	FTimerHandle EntityTimerHandle;

};
