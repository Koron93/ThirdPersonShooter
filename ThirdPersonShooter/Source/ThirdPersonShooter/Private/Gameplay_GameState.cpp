// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay_GameState.h"

void AGameplay_GameState::SetGameState(EGameState aState)
{
	CurrentState = aState;
	OnRep_GameState();
}

void AGameplay_GameState::OnRep_GameState()
{
	OnGameStateChanged.Broadcast(CurrentState);
}