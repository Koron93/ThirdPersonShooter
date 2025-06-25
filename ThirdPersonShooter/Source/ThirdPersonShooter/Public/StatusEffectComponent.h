// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusEffectComponent.generated.h"

class UStatusEffect;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONSHOOTER_API UStatusEffectComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusEffectComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintReadOnly, Category = "Status Effect")
	TArray<UStatusEffect*> ActiveEffects;

	UFUNCTION(BlueprintCallable, Category = "StatusEffect")
	FName RemoveEffect(int i);

	UFUNCTION(BlueprintCallable, Category = "StatusEffect")
	FName AddEffect(UStatusEffect* effect);
};
