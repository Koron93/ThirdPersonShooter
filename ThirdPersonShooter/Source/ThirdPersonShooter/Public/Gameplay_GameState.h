// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Gameplay_GameState.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameStateChanged, EGameState)

UENUM()
enum class EGameState : uint8
{
	InProgress,
	Paused,
	Gameover,
	Cinema
};

UCLASS()
class THIRDPERSONSHOOTER_API AGameplay_GameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly)
	EGameState CurrentState;

	void SetGameState(EGameState aState);

protected:
	UFUNCTION()
	void OnRep_GameState();

private:
	FOnGameStateChanged OnGameStateChanged;
};
