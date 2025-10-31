// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay_GameMode.h"

AGameplay_GameMode::AGameplay_GameMode()
{

}

void AGameplay_GameMode::StartGame()
{
	Super::StartPlay();

	AGameplay_GameState* GS = GetGameState<AGameplay_GameState>();
	if (GS)	GS->SetGameState(EGameState::InProgress);
}