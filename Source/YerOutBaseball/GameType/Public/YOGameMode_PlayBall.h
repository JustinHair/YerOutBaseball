// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "Gameplay/Public/YOBallgame.h"
#include "YOGameMode_PlayBall.generated.h"


/**
 * 
 */
UCLASS()
class YEROUTBASEBALL_API AYOGameMode_PlayBall : public AGameMode
{
	GENERATED_BODY()
public:
	AYOGameMode_PlayBall(const class FObjectInitializer& ObjectInitializer);

private: 
	class AYOBallGame Simulation;
	
	
};
