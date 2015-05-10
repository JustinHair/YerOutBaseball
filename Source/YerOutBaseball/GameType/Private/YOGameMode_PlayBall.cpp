// Fill out your copyright notice in the Description page of Project Settings.

#include "YerOutBaseball.h"
#include "GameType/Public/YOGameMode_PlayBall.h"


AYOGameMode_PlayBall::AYOGameMode_PlayBall(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBlueprint> YOPlayerController(TEXT("Blueprint'/Game/Blueprints/YerOutPlayerController.YerOutPlayerController'"));
	PlayerControllerClass = (UClass*)YOPlayerController.Object->GeneratedClass;

	Simulation.SetGameState(EYOGameStatex::PreGame);
	Simulation.BaseballSimLog.Empty();
}