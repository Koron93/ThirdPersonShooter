// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Gameplay_GameState.h"
#include "Gameplay_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API AGameplay_GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGameplay_GameMode();

	void StartGame();
};
