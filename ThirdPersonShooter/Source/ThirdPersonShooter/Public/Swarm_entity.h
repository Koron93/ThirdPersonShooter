// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Swarm_entity.generated.h"

UENUM(BlueprintType)
enum class EBehaviorState : uint8
{
	Sleepy,
	Patroling,
	Hunting,
	Eating,
	Drinking,
	Dead
};

UCLASS()
class THIRDPERSONSHOOTER_API ASwarm_entity : public AActor
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

	UPROPERTY(BlueprintReadWrite)
	EBehaviorState CurrentState;

	UPROPERTY(BlueprintReadWrite)
	float Hunger;

	UPROPERTY(BlueprintReadWrite)
	float Thirst;

	UPROPERTY(BlueprintReadWrite)
	float Rested;

	UFUNCTION()
	void UpdateEntity(const FVector& NewVelocity);

	UFUNCTION(BlueprintImplementableEvent)
	void Attack();

	UFUNCTION(BlueprintImplementableEvent)
	void Sleep();

	UFUNCTION(BlueprintImplementableEvent)
	void Eat();

	UFUNCTION(BlueprintImplementableEvent)
	void Drink();

	UPROPERTY(EditAnywhere)
	float SleepAnimation;

	UPROPERTY(EditAnywhere)
	float EatAnimation;

	UPROPERTY(EditAnywhere)
	float DrinkAnimation;

	FVector GetVelocity() const { return Velocity; }
	void SetVelocity(const FVector& newVel) { Velocity = newVel; }

private:
	UFUNCTION()
	void CalcValues();

	UFUNCTION()
	void HandleTimer();

	UFUNCTION()
	void HandleAnimtation();

	UFUNCTION()
	void AnimationTimer();

	FTimerHandle EntityTimerHandle;

	FTimerHandle EntityAnimationTime;

	FVector Velocity;
	const float WalkingVelocity = 200.f;
	const float RunningVelocity = 800.f;
};
