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
		FVector boidLocation = Boid->GetActorLocation();
		FVector start = boidLocation + Boid->GetActorForwardVector() * 200.f + FVector(0, 0, 50);
		FVector endLeft = boidLocation + Boid->GetActorForwardVector() + Boid->GetActorRightVector() * -200 + FVector(0, 0, 50);
		FVector endRight = boidLocation + Boid->GetActorForwardVector() + Boid->GetActorRightVector() * 200 + FVector(0, 0, 50);

		FHitResult hitLeft, hitRight;
		bool bIsHitLeft = GetWorld()->LineTraceSingleByChannel(hitLeft, start, endLeft, ECC_Visibility);
		bool bIsHitRight = GetWorld()->LineTraceSingleByChannel(hitRight, start, endRight, ECC_Visibility);

		DrawDebugLine(
			GetWorld(),
			start,
			endLeft,
			FColor::Green,
			false,
			0.1f,
			0,
			2.0f
		);

		DrawDebugLine(
			GetWorld(),
			start,
			endRight,
			FColor::Green,
			false,
			0.1f,
			0,
			2.0f
		);

		FVector objectDistance = FVector(0,0,0);

		if (bIsHitLeft)
		{
			objectDistance += hitLeft.ImpactPoint - boidLocation;

			DrawDebugSphere(
				GetWorld(),
				hitLeft.ImpactPoint,
				10.f,
				2,
				FColor::Red,
				false,
				2.f
			);
		}

		if (bIsHitRight)
		{
			objectDistance -= hitRight.ImpactPoint - boidLocation;

			DrawDebugSphere(
				GetWorld(),
				hitRight.ImpactPoint,
				10.f,
				2,
				FColor::Red,
				false,
				2.f
			);
		}

		if (Boid->CurrentState != EBehaviorState::Hunting)
		{
			if (Boid->Thirst <= 0) Boid -> CurrentState = EBehaviorState::Drinking;
			else if (Boid->Hunger <= 0) Boid->CurrentState = EBehaviorState::Eating;
		}
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

				FVector ToCenter = (GetActorLocation() - BoidLocation).GetSafeNormal();

				FVector NewVelocity =
					Boid->GetVelocity() +
					Cohesion * CohesionWeight +
					Alignment * AlignmentWeight +
					Separation * SeparationWeight +
					(ToCenter.GetSafeNormal() * GlobalCohesionWeight) +
					objectDistance;

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
						FVector ToCenter = (GetActorLocation() - BoidLocation).GetSafeNormal();
						NewVelocity = (FMath::VRand() * 100.f) +
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
		case::EBehaviorState::Hunting:
		{
			FVector BoidLocation = Boid->GetActorLocation();
			Target = Boid->BodyOfIntrest;
			FVector AvgLocation = FVector::ZeroVector;
			FVector AvgVelocity = FVector::ZeroVector;
			FVector Separation = FVector::ZeroVector;
			int32 NeighborCount = 0;
			FVector targetLocation = Boid->BodyOfIntrest->GetActorLocation();

			float DistanceToTarget = FMath::Abs(BoidLocation.X - targetLocation.X) + FMath::Abs(BoidLocation.Y - targetLocation.Y);
			if (DistanceToTarget <= 100)
			{
				Boid->AnimationTimer();
			}

			for (ASwarm_entity* Other : Boids)
			{

				if (Other == Boid ) continue;

				Boid->BodyOfIntrest = Target;
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

			FVector NewVelocity;

			if (NeighborCount > 0) // movement if theres a neighbors
			{
				AvgLocation /= NeighborCount;
				AvgVelocity /= NeighborCount;


				FVector Cohesion = (AvgLocation - BoidLocation).GetSafeNormal();

				FVector Alignment = (AvgVelocity - Boid->GetVelocity()).GetSafeNormal();

				Separation = Separation.GetSafeNormal();

				FVector ToCenter = (targetLocation - BoidLocation).GetSafeNormal();

				NewVelocity =
					Boid->GetVelocity() +
					Cohesion * CohesionWeight +
					Alignment * AlignmentWeight +
					Separation * SeparationWeight +
					(ToCenter.GetSafeNormal() * GlobalCohesionWeight) * 10 +
					objectDistance;

				NewVelocity.Z = 0;
				Boid->UpdateEntity(NewVelocity);
				//UE_LOG(LogTemp, Warning, TEXT("Boid %s has %d neighbors"), *Boid->GetName(), NeighborCount);
			}
			else // if there is no neighbor
			{
				NewVelocity = (targetLocation - BoidLocation).GetSafeNormal() * 1000;
				//UE_LOG(LogTemp, Warning, TEXT("Boid %s"), *Boid->GetName());
			}

			Boid->UpdateEntity(NewVelocity);

			break;
		}
		default:
		{
			FVector BoidLocation = Boid->GetActorLocation();

			FVector AvgLocation = FVector::ZeroVector;
			FVector AvgVelocity = FVector::ZeroVector;
			FVector Separation = FVector::ZeroVector;
			int32 NeighborCount = 0;
			FVector targetLocation = Boid->BodyOfIntrest->GetActorLocation();

			float DistanceToTarget = FMath::Abs(BoidLocation.X - targetLocation.X) + FMath::Abs(BoidLocation.Y - targetLocation.Y);
			if (DistanceToTarget <= 50)
			{
				Boid->UpdateEntity(FVector(0, 0, 0));
				Boid->AnimationTimer();
			}
			else
			{

				for (ASwarm_entity* Other : Boids) 
				{
					if (Other == Boid || Other->CurrentState == EBehaviorState::Patroling) continue;

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

				FVector NewVelocity;

				if (NeighborCount > 0) // movement if theres a neighbors
				{

					AvgLocation /= NeighborCount;
					AvgVelocity /= NeighborCount;


					FVector Cohesion = (AvgLocation - BoidLocation).GetSafeNormal();

					FVector Alignment = (AvgVelocity - Boid->GetVelocity()).GetSafeNormal();

					Separation = Separation.GetSafeNormal();

					FVector ToCenter = (targetLocation - BoidLocation).GetSafeNormal();

					NewVelocity =
						Boid->GetVelocity() +
						Cohesion * CohesionWeight +
						Alignment * AlignmentWeight +
						Separation * SeparationWeight +
						(ToCenter.GetSafeNormal() * GlobalCohesionWeight) +
						objectDistance;

					NewVelocity.Z = 0;
					Boid->UpdateEntity(NewVelocity);
					//UE_LOG(LogTemp, Warning, TEXT("Boid %s has %d neighbors"), *Boid->GetName(), NeighborCount);
				}
				else
				{
					NewVelocity = targetLocation - BoidLocation.GetSafeNormal();
				}

				Boid->UpdateEntity(NewVelocity);
			}
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

