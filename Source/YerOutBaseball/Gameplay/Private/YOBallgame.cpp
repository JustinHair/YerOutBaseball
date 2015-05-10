// Fill out your copyright notice in the Description page of Project Settings.

#include "YerOutBaseball.h"
#include "Gameplay/Public/YOBallgame.h"

DEFINE_LOG_CATEGORY(YOLOG);

bool AYOBallGame::IsBatterBeingIntentionallyWalked()
{
	//Fielding Teams coach will make this decision based on several different factors.

	return false;
}

EYOGameStatex::Type AYOBallGame::GetCurrentGameState() const
{
	return CurrentGameState;
}

void AYOBallGame::SetGameState(EYOGameStatex::Type NewState)
{
	CurrentGameState = NewState;
	HandleNewStates(CurrentGameState);
}

void AYOBallGame::HandleNewStates(EYOGameStatex::Type NewState)
{
	switch (NewState)
	{
	case EYOGameStatex::InTheMenus:
		break;
	case EYOGameStatex::PreGame:
		break;
	case EYOGameStatex::BeforeThePlay:
		break;
	case EYOGameStatex::AtBatInProgress:
		IsBatterBeingIntentionallyWalked();
		break;
	case EYOGameStatex::BallInPlay:
		break;
	case EYOGameStatex::PlayResolution:
		break;
	case EYOGameStatex::Unknown:
	default:
		//Nothing happens.
		break;
	}
}

void AYOBallGame::PrintBaseballSimLog()
{
	for (int32 i = 0; i < BaseballSimLog.Num(); i++)
	{
		UE_LOG(YOLOG, Log, TEXT("%s"), *BaseballSimLog[i]);
	}
}