// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Swarm_entity.h"
#include "Swarm_Manager.generated.h"

UCLASS()
class THIRDPERSONSHOOTER_API ASwarm_Manager : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASwarm_Manager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<ASwarm_entity> BoidClass;

	UPROPERTY(BlueprintReadOnly)
	TArray<ASwarm_entity*> Boids;

	UPROPERTY(BlueprintReadWrite)
	AActor* Target;


private:
	TMap<FIntVector, TArray<ASwarm_entity*>> SpacialHash;
	const float CellSize = 400.f;

	FIntVector GetCellCoordinates(const FVector& aPosition)
	{
		return FIntVector(
			FMath::FloorToInt(aPosition.X/ CellSize),
			FMath::FloorToInt(aPosition.Y / CellSize),
			0
		);
	}

	void UpdateGrid();

	const int NumberOfBoids = 15;
	const float BoidSpawnRadius = 500.f;
	const float SeperationDistance = 250.f;
	const float CohesionWeight = 0.6f;
	const float AlignmentWeight = 0.4f;
	const float SeparationWeight = 1.8f;
	const float GlobalCohesionWeight = 0.8f;
	const float AvoidanceStrenght = 0.1f;
};
