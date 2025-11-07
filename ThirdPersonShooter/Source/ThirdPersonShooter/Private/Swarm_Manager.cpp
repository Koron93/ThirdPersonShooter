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

	UpdateGrid();

	for (ASwarm_entity* Boid : Boids)
	{
		if (!Boid) continue;
		FVector boidLocation = Boid->GetActorLocation();
		FVector start = boidLocation + Boid->GetActorForwardVector() * 200.f + FVector(0, 0, 50);
		FVector endLeft = boidLocation + Boid->GetActorForwardVector() + Boid->GetActorRightVector() * -100 + FVector(0, 0, 50);
		FVector endRight = boidLocation + Boid->GetActorForwardVector() + Boid->GetActorRightVector() * 100 + FVector(0, 0, 50);

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

		FVector objectAvoidance = FVector(0,0,0);

		if (bIsHitLeft)
		{
			FVector impactDirection = hitLeft.ImpactPoint - boidLocation;

			FVector laterialDirection = impactDirection - FVector::DotProduct(
				impactDirection, 
				Boid->GetActorForwardVector()
			) * 
				Boid->GetActorForwardVector();

			if (!laterialDirection.IsNearlyZero())
			{
				laterialDirection.Normalize();
				objectAvoidance -= laterialDirection;

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
		}

		if (bIsHitRight)
		{
			FVector impactDirection = hitRight.ImpactPoint - boidLocation;

			FVector laterialDirection = impactDirection - 
				FVector::DotProduct( impactDirection,
				Boid->GetActorForwardVector()
			) *
				Boid->GetActorForwardVector();

			if (!laterialDirection.IsNearlyZero())
			{
				laterialDirection.Normalize();
				objectAvoidance += laterialDirection;

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
		}
		if (bIsHitRight && bIsHitLeft && objectAvoidance.IsNearlyZero())
		{
			objectAvoidance += Boid->GetActorRightVector() * 2;
		}

		if (Target != nullptr) {
			Boid->BodyOfIntrest = Target;
			Boid->CurrentState = EBehaviorState::Hunting;
		}

		if (Boid->CurrentState != EBehaviorState::Hunting)
		{
			//if (Boid->Thirst <= 0) Boid -> CurrentState = EBehaviorState::Drinking;
			//else if (Boid->Hunger <= 0) Boid->CurrentState = EBehaviorState::Eating;
			//else 
			if (Boid->Rested <= 0)	Boid->CurrentState = EBehaviorState::Sleepy;
		}
		//UE_LOG(LogTemp, Warning, TEXT("Boid state: %s"), *UEnum::GetValueAsString(Boid->CurrentState));

		TArray<ASwarm_entity*> Neighbors;
		switch (Boid->CurrentState)
		{
		case::EBehaviorState::Patroling:
		{

			FVector BoidLocation = Boid->GetActorLocation();

			FVector AvgLocation = FVector::ZeroVector;
			FVector AvgVelocity = FVector::ZeroVector;
			FVector Separation = FVector::ZeroVector;
			int32 NeighborCount = 0;

			Neighbors = GetNeighbors(Boid->GetActorLocation());
			if (Neighbors.Num() > 0) {
				for (ASwarm_entity* Other : Neighbors)
				{
					if (Other == Boid) continue;

					FVector ToOther = Other->GetActorLocation() - BoidLocation;
					float Distance = ToOther.Size();
					AvgLocation += Other->GetActorLocation();
					AvgVelocity += Other->GetVelocity();

					if (Distance < SeperationDistance)
					{
						Separation -= (ToOther.GetSafeNormal() / Distance) * 2;
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
					(Cohesion * CohesionWeight) +
					(Alignment * AlignmentWeight) +
					(Separation * SeparationWeight) +
					(ToCenter.GetSafeNormal() * GlobalCohesionWeight) +
					(objectAvoidance / AvoidanceStrenght);

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
						NewVelocity += (ToCenter.GetSafeNormal() * GlobalCohesionWeight) +
							(objectAvoidance / AvoidanceStrenght);
					}
					NewVelocity.Z = 0;
					//UE_LOG(LogTemp, Warning, TEXT("Boid %s"), *Boid->GetName());
				}
				else {
					FVector ToCenter = (GetActorLocation() - BoidLocation);
					if (!ToCenter.IsNearlyZero())
					{
						NewVelocity += (ToCenter.GetSafeNormal() * GlobalCohesionWeight) +
							(objectAvoidance / AvoidanceStrenght);
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

			Neighbors = GetNeighbors(Boid->GetActorLocation());
			if (Neighbors.Num() > 0) {
				for (ASwarm_entity* Other : Neighbors)
				{
					if (Other == Boid) continue;

					FVector ToOther = Other->GetActorLocation() - BoidLocation;
					float Distance = ToOther.Size();
					AvgLocation += Other->GetActorLocation();
					AvgVelocity += Other->GetVelocity();

					if (Distance < SeperationDistance)
					{
						Separation -= (ToOther.GetSafeNormal() / Distance) * 2;
					}

					NeighborCount++;
				}
			}

			FVector targetLocation = Target->GetActorLocation();

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
					(Cohesion * CohesionWeight) +
					(Alignment * AlignmentWeight) +
					(Separation * SeparationWeight) +
					(ToCenter.GetSafeNormal() / GlobalCohesionWeight) +
					objectAvoidance;

				NewVelocity.Z = 0;
				//UE_LOG(LogTemp, Warning, TEXT("Boid %s has %d neighbors"), *Boid->GetName(), NeighborCount);
			}
			else // if there is no neighbor
			{
				NewVelocity = (targetLocation - BoidLocation).GetSafeNormal() +
					objectAvoidance;
				//UE_LOG(LogTemp, Warning, TEXT("Boid %s"), *Boid->GetName());
			}

			Boid->UpdateEntity(NewVelocity);

			break;
		}
		case::EBehaviorState::Sleepy:
		{
			if (Boid->Rested >= 120) Boid->CurrentState = EBehaviorState::Patroling;
				Boid->UpdateEntity(FVector(0, 0, 0));
				Boid->AnimationTimer();

			break;
		}
		default:
		{
			FVector BoidLocation = Boid->GetActorLocation();

			FVector AvgLocation = FVector::ZeroVector;
			FVector AvgVelocity = FVector::ZeroVector;
			FVector Separation = FVector::ZeroVector;
			int32 NeighborCount = 0;
			FVector targetLocation = GetActorLocation()  + 
				FVector(
				FMath::RandRange(-100.0f, 100.0f),
				FMath::RandRange(-100.0f, 100.0f),
					0
			);;
			if(Boid->BodyOfIntrest != nullptr)	targetLocation = Boid->BodyOfIntrest->GetActorLocation();

			float DistanceToTarget = FMath::Abs(BoidLocation.X - targetLocation.X) + FMath::Abs(BoidLocation.Y - targetLocation.Y);
			if (DistanceToTarget <= 50)
			{
				Boid->UpdateEntity(FVector(0, 0, 0));
				Boid->AnimationTimer();
			}
			else
			{
				Neighbors = GetNeighbors(Boid->GetActorLocation());
				if (Neighbors.Num() > 0) {
					for (ASwarm_entity* Other : Neighbors)
					{
						if (Other == Boid) continue;

						FVector ToOther = Other->GetActorLocation() - BoidLocation;
						float Distance = ToOther.Size();
						AvgLocation += Other->GetActorLocation();
						AvgVelocity += Other->GetVelocity();

						if (Distance < SeperationDistance)
						{
							Separation -= (ToOther.GetSafeNormal() / Distance) * 2;
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
						(Cohesion * CohesionWeight) +
						(Alignment * AlignmentWeight) +
						(Separation * SeparationWeight) +
						(ToCenter.GetSafeNormal() / GlobalCohesionWeight) +
						objectAvoidance;

					NewVelocity.Z = 0;
					//UE_LOG(LogTemp, Warning, TEXT("Boid %s has %d neighbors"), *Boid->GetName(), NeighborCount);
				}
				else
				{
					NewVelocity = targetLocation - BoidLocation.GetSafeNormal() +
						objectAvoidance;
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

TArray<ASwarm_entity*> ASwarm_Manager::GetNeighbors(FVector aVector)
{

	FIntVector baseCell = GetCellCoordinates(aVector);
	TArray<ASwarm_entity*> neighbors;

	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			FIntVector neighborCell = baseCell + FIntVector(x, y, 0);
			if (TArray<ASwarm_entity*>* Cell = SpacialHash.Find(neighborCell))
			{
				neighbors.Append(*Cell);
			}
		}
	}
	return neighbors;
}

void ASwarm_Manager::UpdateGrid()
{
	SpacialHash.Empty();

	for (ASwarm_entity* entity : Boids)
	{
		if (!entity) continue;

		FVector pos = entity->GetActorLocation();

		FIntVector cell = GetCellCoordinates(pos);

		TArray<ASwarm_entity*>& CellArray = SpacialHash.FindOrAdd(cell);
		CellArray.Add(entity);
	}
}