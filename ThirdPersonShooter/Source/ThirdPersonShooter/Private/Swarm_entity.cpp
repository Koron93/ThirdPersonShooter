// Fill out your copyright notice in the Description page of Project Settings.


#include "Swarm_entity.h"
#include "TimerManager.h"

// Sets default values
ASwarm_entity::ASwarm_entity()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentState = BehaviorState::Patroling; 
	Hunger = FMath::RandRange(300, 400);
	Thirst = FMath::RandRange(150, 350);
	Rested = FMath::RandRange(300, 600);
}

// Called when the game starts or when spawned
void ASwarm_entity::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		EntityTimerHandle,
		this,
		&ASwarm_entity::HandleTimer, 
		1.0f,                        
		true                         
	);
}

// Called every frame
void ASwarm_entity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASwarm_entity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ASwarm_entity::CalcValues()
{
	Hunger -= 1;
	Thirst -= 1;
	Rested -= 1;

	if (Thirst <= 30)
	{
		CurrentState = BehaviorState::Thirsty;
	}
	else if (Hunger <= 30)
	{
		CurrentState = BehaviorState::Hungry;
	}
	else if (Rested <= 10)
	{
		CurrentState = BehaviorState::Sleepy;
	}
	else
	{
		CurrentState = BehaviorState::Patroling;
	}
}

void ASwarm_entity::HandleTimer()
{
	CalcValues();
}