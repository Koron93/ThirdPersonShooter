// Fill out your copyright notice in the Description page of Project Settings.


#include "Swarm_entity.h"
#include "TimerManager.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASwarm_entity::ASwarm_entity()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CurrentState = EBehaviorState::Patroling; 
	Hunger = FMath::RandRange(50, 400);
	Thirst = FMath::RandRange(50, 350);
	Rested = FMath::RandRange(50, 600);
}

// Called when the game starts or when spawned
void ASwarm_entity::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		EntityTimerHandle,
		this,
		&ASwarm_entity::HandleTimer, 
		0.5f,                        
		true                         
	);
}

// Called every frame
void ASwarm_entity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentLocation = GetActorLocation();
	FVector newLocation = currentLocation + Velocity * DeltaTime;
	SetActorLocation(newLocation); //Updated Position

	FVector direction = Velocity.GetSafeNormal();
	direction.Z = 0;

	if (!direction.IsNearlyZero()) //Applie rotation over time
	{
		FRotator newRotation;

		FRotator TargetRotation = direction.Rotation();
		TargetRotation.Pitch = 0.0f;
		TargetRotation.Roll = 0.0f;

		FRotator SmoothedRotation = FMath::RInterpTo(
			GetActorRotation(),
			TargetRotation,
			DeltaTime,
			5.0f
		);

		//GroundCheck
		FHitResult HitGround;
		FVector StartGround = GetActorLocation() + FVector(0, 0, 50);
		FVector EndGround = GetActorLocation() - FVector(0, 0, 200);

		if (GetWorld()->LineTraceSingleByChannel(HitGround, StartGround, EndGround, ECC_Visibility))
		{
			FVector GroundPos = HitGround.ImpactPoint + FVector(0, 0, 5.f);
			SetActorLocation(FVector(newLocation.X, newLocation.Y, GroundPos.Z));

			FVector vectorUp = HitGround.ImpactNormal;
			FVector vectorForward = SmoothedRotation.Vector();
			newRotation = UKismetMathLibrary::MakeRotFromXZ(vectorForward, vectorUp);
		}
		else {
			FHitResult hitSky;
			FVector startSky = GetActorLocation() + FVector(0, 0, 50);
			FVector endSky = GetActorLocation() + FVector(0, 0, 500);
			if (GetWorld()->LineTraceSingleByChannel(hitSky, startSky, endSky, ECC_Visibility))
			{
				FVector GroundPos = hitSky.ImpactPoint + FVector(0, 0, 5.f);
				SetActorLocation(FVector(newLocation.X, newLocation.Y, GroundPos.Z));
			}
		}
		SetActorRotation(newRotation);
	}
	//UE_LOG(LogTemp, Warning, TEXT("Boid %s velocity: %s"), *GetName(), *Velocity.ToString());
}

void ASwarm_entity::CalcValues()
{
	Hunger -= 1;
	Thirst -= 1;
	Rested -= 1;

}

void ASwarm_entity::HandleTimer()
{
	CalcValues();
}

void ASwarm_entity::HandleAnimtation()
{
	switch (CurrentState)
	{
	case::EBehaviorState::Eating:
	{
		Eat();
		break;
	}
	case::EBehaviorState::Drinking:
	{
		Drink();
		break;
	}
	case::EBehaviorState::Sleepy:
	{
		Sleep();
		break;
	}
	case::EBehaviorState::Hunting:
	{
		Attack();
		break;
	}
	}
}

void ASwarm_entity::AnimationTimer()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(EntityAnimationTime))
	{
		return;
	}

	switch (CurrentState)
	{
	case::EBehaviorState::Eating:
		{
		GetWorld()->GetTimerManager().SetTimer(
			EntityAnimationTime,
			this,
			&ASwarm_entity::HandleAnimtation,
			EatAnimation,
			false
		);
			break;
		}
	case::EBehaviorState::Sleepy:
		{
		GetWorld()->GetTimerManager().SetTimer(
			EntityAnimationTime,
			this,
			&ASwarm_entity::HandleAnimtation,
			SleepAnimation,
			false
		);
			break;
		}
	case::EBehaviorState::Drinking:
	{
		GetWorld()->GetTimerManager().SetTimer(
			EntityAnimationTime,
			this,
			&ASwarm_entity::HandleAnimtation,
			DrinkAnimation,
			false
		);
		break;
	}
	case::EBehaviorState::Hunting:
	{
		GetWorld()->GetTimerManager().SetTimer(
			EntityAnimationTime,
			this,
			&ASwarm_entity::HandleAnimtation,
			DrinkAnimation,
			false
		);
		break;
	}
	}
}

void ASwarm_entity::UpdateEntity(const FVector& NewVelocity)
{
	switch (CurrentState)
	{
	case::EBehaviorState::Hunting:
	{
		Velocity = NewVelocity.GetClampedToMaxSize(RunningVelocity);
		break;
	}
	case::EBehaviorState::Patroling:
	{
		Velocity = NewVelocity.GetClampedToMaxSize(WalkingVelocity);
		break;
	}
	case::EBehaviorState::Drinking:
	{
		Velocity = NewVelocity.GetClampedToMaxSize(RunningVelocity);
		break;
	}
	case::EBehaviorState::Eating:
	{
		Velocity = NewVelocity.GetClampedToMaxSize(RunningVelocity);
		break;
	}
	case::EBehaviorState::Sleepy:
	{
		Velocity = NewVelocity.GetClampedToMaxSize(WalkingVelocity);
		break;
	}
	default:
	{
		Velocity = FVector(0, 0, 0);
		break;
	}
	}
}


