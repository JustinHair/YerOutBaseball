// Fill out your copyright notice in the Description page of Project Settings.

#include "YerOutBaseball.h"
#include "YOGameMode.h"
#include "YOGameState.h"


//DEFINE_LOG_CATEGORY(YOLOG);


AYOGameMode::AYOGameMode(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	//Blueprint HUD to use.
	static ConstructorHelpers::FObjectFinder<UBlueprint> YOHUD(TEXT("Blueprint'/Game/Blueprints/YOHUD.YOHUD'"));
	HUDClass = (UClass*)YOHUD.Object->GeneratedClass;

	static ConstructorHelpers::FObjectFinder<UBlueprint> YOPlayerController(TEXT("Blueprint'/Game/Blueprints/YerOutPlayerController.YerOutPlayerController'"));
	PlayerControllerClass = (UClass*)YOPlayerController.Object->GeneratedClass;
	
	//Custom game state class to use.
	GameStateClass = AYOGameState::StaticClass();

	//Current state of the simulation
	CurrentState = EYOGameState::InTheMenus;
	Outs = EYOOuts::ZeroOuts;

	//Batter Setup
	CurrentBatter.BatterName = TEXT("Unknown Batter");
	CurrentBatter.ID = NULL;
	CurrentBatter.LineupOrderNumber = 1;
	CurrentBatter.Contact = 500;
	CurrentBatter.SCRight = 33;
	CurrentBatter.SCCenter = 34;
	CurrentBatter.SCLeft = 33;
	CurrentBatter.BatterFlyballTendency = 3;
	CurrentBatter.Power = 350;
	CurrentBatter.BatHand = TEXT("R");

	//Pitcher Setup
	CurrentPitcher.PitcherName = TEXT("Unknown Pitcher");
	CurrentPitcher.ID = NULL;
	CurrentPitcher.ThrowHand = TEXT("R");
	CurrentPitcher.PitchSpeedFastest = 85;
	CurrentPitcher.PitchSpeedSlowest = 75;
	CurrentPitcher.PitchControl = 100;
	CurrentPitcher.PitchMovement = 300;
	CurrentPitcher.FlyBallTendency = EYOFlyBallTendency::Medium;

	//Base Paths
	CurrentBaseState.ResetAllBases();
	CurrentBaseState.RunnerSlots.Add(CurrentBaseState.RunnerA);
	CurrentBaseState.RunnerSlots.Add(CurrentBaseState.RunnerB);
	CurrentBaseState.RunnerSlots.Add(CurrentBaseState.RunnerC);
	CurrentBaseState.RunnerSlots.Add(CurrentBaseState.RunnerD);
	
	//Ball In Field setup
	TheBallIsInPlay.ResetBallHitLocations();
	TheBallIsInPlay.HitBallDistance = 0;
	TheBallIsInPlay.ResetBallHitHeight();

	//Team strategies
	Strategy.bIsIBB = false;
	Strategy.bIsBunting = false;

	//Home and visiting Team Score
	int32 TempScore = 0;

	//Default Ball Park Dimensions
	BallPark.ParkName = TEXT("Default Park");
	BallPark.ID = NULL;
	BallPark.LeftFieldWallDistance = 330;
	BallPark.LeftCenterWallDistance = 360;
	BallPark.CenterWallDistance = 405;
	BallPark.RightCenterWallDistance = 360;
	BallPark.RightFieldWallDistance = 330;
	BallPark.LeftFieldWallHeight = 8;
	BallPark.LeftCenterWallHeight = 8;
	BallPark.CenterWallHeight = 8;
	BallPark.RightCenterWallHeight = 8;
	BallPark.RightFieldWallHeight = 8;

	BaseballSimLog.Add(TEXT("Welcome to YerOut Baseball\n"));
}

void AYOGameMode::SetCurrentState(EYOGameState::Type NewState)
{
	CurrentState = NewState;

	HandleNewStates(NewState);
}


void AYOGameMode::HandleNewStates(EYOGameState::Type NewState)
{
	//Get the game state being used so we can use it's functions.
	AYOGameState* SimState = Cast<AYOGameState>(UGameplayStatics::GetGameState(this));

	switch (NewState)
	{
	case EYOGameState::InTheMenus:
		break;
	case EYOGameState::PreGame:
		break;
	case EYOGameState::BeforeThePlay:
		break;	
	case EYOGameState::AtBatInProgress:
		BaseballSimLog.Empty();
		SimState->DetermineIfIBB(CurrentBatter, Strategy, CurrentBaseState);
		SimState->DetermineIfBatterBunts(CurrentBatter, Strategy);
		SimState->DetermineIfBallBattedIntoPlay(CurrentBatter, CurrentPitcher);
		SimState->DetermineIfBatterWalked(CurrentBatter, CurrentPitcher, CurrentBaseState);
		SimState->BatterStruckOut();
		break;
	case EYOGameState::BallInPlay:
		CurrentBaseState.ConvertBatterToBaseRunner(CurrentBatter);
		SimState->BattedBallType(CurrentBatter,CurrentPitcher,TheBallIsInPlay);
		SimState->BattedBallLocation(CurrentBatter,CurrentPitcher, TheBallIsInPlay);
		SimState->BattedBallDistance(CurrentBatter, TheBallIsInPlay, Strategy);
		SimState->DetermineIfHomerun(TheBallIsInPlay, Strategy, BallPark, CurrentBaseState);

		SetCurrentState(EYOGameState::PlayResolution);
		break;
	case EYOGameState::PlayResolution:
		BaseballSimLog.Add(TEXT("...\n"));
		SimState->PlayResolution(TheBallIsInPlay, CurrentBaseState);
		BaseballSimLogging();
		break;
	case EYOGameState::Unknown:
	default:
		//Nothing happens.
		break;
	}
}

void AYOGameMode::SetCurrentBatter(FCurrentBatter NewBatter)
{
	CurrentBatter = NewBatter;
}

void AYOGameMode::SetCurrentPitcher(FCurrentPitcher NewPitcher)
{
	CurrentPitcher = NewPitcher;
}

void AYOGameMode::SetBallInPlay(FBallInPlay NewBallInPlay)
{
	TheBallIsInPlay = NewBallInPlay;
}

void AYOGameMode::SetStrategy(FCoachStrategy NewStrategy)
{
	Strategy = NewStrategy;
}

void AYOGameMode::SetBasePathState(FCurrentBaseStates NewBaseState)
{
	CurrentBaseState = NewBaseState;
}

void AYOGameMode::SetOuts(EYOOuts::Type NewOuts)
{
	Outs = NewOuts;
}

void AYOGameMode::IncrementNumberOfOuts()
{
	if (Outs == EYOOuts::ThreeOuts)
	{
		SetCurrentState(EYOGameState::PlayResolution);
		return;
	}
	else if (Outs == EYOOuts::TwoOuts)
	{
		Outs = EYOOuts::ThreeOuts;
		SetCurrentState(EYOGameState::PlayResolution);
		return;
	}
	else if (Outs == EYOOuts::OneOut)
	{
		Outs = EYOOuts::TwoOuts;
		return;
	}
	else if (Outs == EYOOuts::ZeroOuts)
	{
		Outs = EYOOuts::OneOut;
		return;
	}
	
	Outs = EYOOuts::OneOut;

}


void AYOGameMode::BaseballSimLogging()
{
	for (int32 i = 0; i < BaseballSimLog.Num(); i++)
	{
		UE_LOG(YOLOG, Log, TEXT("%s"), *BaseballSimLog[i]);
	}
}

void AYOGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentState(EYOGameState::InTheMenus);
}