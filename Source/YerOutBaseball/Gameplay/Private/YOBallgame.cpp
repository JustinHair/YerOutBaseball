// Fill out your copyright notice in the Description page of Project Settings.

#include "YerOutBaseball.h"
#include "Gameplay/Public/YOBallgame.h"

YOBallgame::YOBallgame()
{
}

YOBallgame::~YOBallgame()
{
}


void YOBallgame::SetGameState(EYOGameState::Type NewState)
{
	CurrentGameState = NewState;
	HandleNewStates(CurrentGameState);
}

void YOBallgame::HandleNewStates(EYOGameState::Type NewState)
{
	switch (NewState)
	{
	case EYOGameState::InTheMenus:
		break;
	case EYOGameState::PreGame:
		break;
	case EYOGameState::BeforeThePlay:
		break;
	case EYOGameState::AtBatInProgress:
		break;
	case EYOGameState::BallInPlay:
		break;
	case EYOGameState::PlayResolution:
		break;
	case EYOGameState::Unknown:
	default:
		//Nothing happens.
		break;
	}
}