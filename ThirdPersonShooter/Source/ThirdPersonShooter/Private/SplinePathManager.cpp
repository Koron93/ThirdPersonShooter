// Fill out your copyright notice in the Description page of Project Settings.


#include "SplinePathManager.h"

// Sets default values for this component's properties
USplinePathManager::USplinePathManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USplinePathManager::BeginPlay()
{
	Super::BeginPlay();

	int numberOfSplines = FMath::RandRange(5, 10);
	for (int i = 0; i < numberOfSplines; i++)
	{
		int numberOfPoints = FMath::RandRange(5, 12);
		float splinePathOffset = 2 * PI / numberOfSplines;

		FSplinePath currentPath;

		currentPath.NumberOfPoints = numberOfPoints;
		currentPath.Points.SetNum(numberOfPoints);
		float splineSize = FMath::RandRange(75000.f, 100000.f);

		float direction = (splinePathOffset * i);
		FVector newDirection = FVector(
			FMath::Cos(direction), // X-Axis
			FMath::Sin(direction), // Y-Axis
			0					   // Z-Axis
		);
		
		for (int y = 0; y < numberOfPoints; y++)
		{
			
			FVector baseVector = (newDirection * splineSize * y / (numberOfPoints - 1));

			float pointCurve = FMath::RandRange(0.f, 2 * PI);

			if (y < numberOfPoints - 1 || y > 0)
			{
				FVector perp = FVector(-newDirection.Y, newDirection.X, 0.f).GetSafeNormal();
				float aCurve = FMath::RandRange(-10000, 10000);

				currentPath.Points[y] = baseVector + perp * aCurve;
			}
			else if (y == 0)
			{
				currentPath.Points[y] = FVector(0, 0, 0);
			}
			else {
				currentPath.Points[y] = baseVector;
			}
		}

		SplineData.Add(currentPath);
	}
	for(int x = 0; x < SplineData.Num(); x++)
	{
		for (int y = 0; y < SplineData[x].Points.Num() - 1; y++)
		{
			DrawDebugLine(
				GetWorld(),
				SplineData[x].Points[y],
				SplineData[x].Points[y + 1],
				FColor::Yellow,
				true,
				5.f,
				0,
				5.f
			);

			DrawDebugSphere(GetWorld(), SplineData[x].Points[y], 100.f, 16, FColor::Red, true, 10.f);
			UE_LOG(LogTemp, Warning, TEXT("Point %d: %s"), y, *SplineData[x].Points[y].ToString());
		}
	}
}


// Called every frame
void USplinePathManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

