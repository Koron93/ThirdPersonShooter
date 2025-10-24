// Fill out your copyright notice in the Description page of Project Settings.


#include "Swarm_Manager.h"

// Sets default values
ASwarm_Manager::ASwarm_Manager()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Target = nullptr;
}

// Called when the game starts or when spawned
void ASwarm_Manager::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < NumberOfBoids; i++)
	{
		FVector SpawnLocation = FVector(GetActorLocation().X + FMath::RandRange(-BoidSpawnRadius, BoidSpawnRadius), GetActorLocation().Y + FMath::RandRange(-BoidSpawnRadius, BoidSpawnRadius), 0);
		FRotator SpawnRotation = FRotator::ZeroRotator;

		ASwarm_entity* boid = GetWorld()->SpawnActor<ASwarm_entity>(BoidClass, SpawnLocation, SpawnRotation);
		if (boid)
		{
			Boids.Add(boid);
		}
	}
}

// Called every frame
void ASwarm_Manager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	for (ASwarm_entity* Boid : Boids)
	{
		if (!Boid) continue;

		//UE_LOG(LogTemp, Warning, TEXT("Boid state: %s"), *UEnum::GetValueAsString(Boid->CurrentState));

		switch (Boid->CurrentState)
		{
		case::EBehaviorState::Patroling:
		{

			FVector BoidLocation = Boid->GetActorLocation();

			FVector AvgLocation = FVector::ZeroVector;
			FVector AvgVelocity = FVector::ZeroVector;
			FVector Separation = FVector::ZeroVector;
			int32 NeighborCount = 0;

			for (ASwarm_entity* Other : Boids)
			{
				if (Other == Boid) continue;

				FVector ToOther = Other->GetActorLocation() - BoidLocation;
				float Distance = ToOther.Size();

				if (Distance < NeigborRadius)
				{
					AvgLocation += Other->GetActorLocation();
					AvgVelocity += Other->GetVelocity();

					if (Distance < SeperationDistance)
					{
						Separation -= ToOther.GetSafeNormal() / Distance;
					}

					NeighborCount++;
				}
			}

			if (NeighborCount > 0) // movement if theres a neighbors
			{
				AvgLocation /= NeighborCount;
				AvgVelocity /= NeighborCount;


				FVector Cohesion = (AvgLocation - BoidLocation).GetSafeNormal();

				FVector Alignment = (AvgVelocity - Boid->GetVelocity()).GetSafeNormal();

				Separation = Separation.GetSafeNormal();

				FVector NewVelocity =
					Boid->GetVelocity() +
					Cohesion * CohesionWeight +
					Alignment * AlignmentWeight +
					Separation * SeparationWeight;

				FVector ToCenter = (GetActorLocation() - BoidLocation).GetSafeNormal();
				NewVelocity += ToCenter.GetSafeNormal() * GlobalCohesionWeight;

				NewVelocity.Z = 0;
				Boid->UpdateEntity(NewVelocity);
				//UE_LOG(LogTemp, Warning, TEXT("Boid %s has %d neighbors"), *Boid->GetName(), NeighborCount);
			}
			else // if no Neighbors
			{
				FVector NewVelocity = Boid->GetVelocity();
				if (FVector::Dist(Boid->GetActorLocation(), GetActorLocation()) < 1000)
				{
					if (NewVelocity.IsNearlyZero())
					{
						NewVelocity = FMath::VRand() * 100.f;
					}

					FVector ToCenter = (GetActorLocation() - BoidLocation).GetSafeNormal();
					if (!ToCenter.IsNearlyZero())
					{
						NewVelocity += ToCenter.GetSafeNormal() * GlobalCohesionWeight;
					}
					NewVelocity.Z = 0;
					//UE_LOG(LogTemp, Warning, TEXT("Boid %s"), *Boid->GetName());
				}
				else {
					FVector ToCenter = (GetActorLocation() - BoidLocation);
					if (!ToCenter.IsNearlyZero())
					{
						NewVelocity += ToCenter.GetSafeNormal() * GlobalCohesionWeight;
					}
					NewVelocity.Z = 0;
					//UE_LOG(LogTemp, Warning, TEXT("Boid %s velocity: %s"), *Boid->GetName(), *NewVelocity.ToString());
				}
				Boid->UpdateEntity(NewVelocity);
			}
			break;
		}
		case::EBehaviorState::Dead:
		{
			FVector BoidLocation = Boid->GetActorLocation();

			FVector AvgLocation = FVector::ZeroVector;
			FVector AvgVelocity = FVector::ZeroVector;
			FVector Separation = FVector::ZeroVector;
			int32 NeighborCount = 0;

			for (ASwarm_entity* Other : Boids)
			{
				if (Other == Boid) continue;

				FVector ToOther = Other->GetActorLocation() - BoidLocation;
				float Distance = ToOther.Size();

				if (Distance < NeigborRadius)
				{
					AvgLocation += Other->GetActorLocation();
					AvgVelocity += Other->GetVelocity();

					if (Distance < SeperationDistance)
					{
						Separation -= ToOther.GetSafeNormal() / Distance;
					}

					NeighborCount++;
				}
			}

			if (NeighborCount > 0) // movement if theres a neighbors
			{
				AvgLocation /= NeighborCount;
				AvgVelocity /= NeighborCount;


				FVector Cohesion = (AvgLocation - BoidLocation).GetSafeNormal();

				FVector Alignment = (AvgVelocity - Boid->GetVelocity()).GetSafeNormal();

				Separation = Separation.GetSafeNormal();

				FVector NewVelocity =
					Boid->GetVelocity() +
					Cohesion * CohesionWeight +
					Alignment * AlignmentWeight +
					Separation * SeparationWeight;

				FVector ToCenter = (Target->GetActorLocation() - BoidLocation).GetSafeNormal();
				if (!ToCenter.IsNearlyZero())
				{
					NewVelocity += ToCenter.GetSafeNormal() * GlobalCohesionWeight;
				}

				NewVelocity.Z = 0;
				Boid->UpdateEntity(NewVelocity);
			}
			else // if no other movementlogic exists
			{
				FVector NewVelocity = Boid->GetVelocity();

				if (NewVelocity.IsNearlyZero())
				{
					NewVelocity = FMath::VRand() * 100.f;
					NewVelocity.Z = 0;
				}

				Boid->UpdateEntity(NewVelocity);
			}
			break;
		}
		default:
		{
			FVector NewVelocity = FVector(0,0,0);
			Boid->UpdateEntity(NewVelocity);
			break;
		}
		}

	}
}

// Called to bind functionality to input
void ASwarm_Manager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

