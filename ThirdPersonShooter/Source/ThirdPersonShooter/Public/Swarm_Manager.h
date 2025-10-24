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
	const int NumberOfBoids = 9;
	const float BoidSpawnRadius = 400.f;
	const float NeigborRadius = 250.f;
	const float SeperationDistance = 200.f;
	const float CohesionWeight = 0.6f;
	const float AlignmentWeight = 0.2f;
	const float SeparationWeight = 1.3f;
	const float GlobalCohesionWeight = 1.1f;
};
