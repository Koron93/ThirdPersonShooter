// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SplinePathManager.generated.h"

USTRUCT(BlueprintType)
struct FSplinePath
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 NumberOfPoints;

	UPROPERTY(BlueprintReadOnly)
	TArray<FVector> Points;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONSHOOTER_API USplinePathManager : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USplinePathManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	TArray<FSplinePath> SplineData;
};
