// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusEffectComponent.generated.h"

struct FStatusEffect;

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
	UPROPERTY(BlueprintReadOnly, Category = "Status Effect")
	TArray<FStatusEffect> ActiveEffects;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = "StatusEffect")
	FName RemoveEffect(int i);

	UFUNCTION(BlueprintCallable, Category = "StatusEffect")
	FName AddEffect(FStatusEffect effect);

	UFUNCTION(BlueprintCallable, Category = "StatusEffect")
	void StatusUpdate(float deltaTime, TArray<int32>& DamageAmount, TArray<EDamageTypeEnum>& DamageType, bool& canMove, bool& isBuff);
};
