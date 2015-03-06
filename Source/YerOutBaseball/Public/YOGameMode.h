// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameMode.h"
#include "YOBatterPitcher.h"
#include "YORunningAndFielding.h"
#include "YOBallParks.h"
#include "YOGameMode.generated.h"





//enum to store the current state of the game.
UENUM(BlueprintType)
namespace EYOGameState
{
	enum Type
	{
		InTheMenus,			// Player is in the menus
		PreGame,			// Game processes the line ups
		BeforeThePlay,		// Strategy and attribute changes before the pitcher throws the ball.
		AtBatInProgress,	// Deciding who wins in the battle between pitcher and batter.
		BallInPlay,			// Ball is now in play.
		PlayResolution,		// Move runners, set new outs, capture current game stats
		Unknown,			// Who knows what happened...
	};
}

//enum to store the current state of the game.
UENUM(BlueprintType)
namespace EYOOuts
{
	enum Type
	{
		ZeroOuts,
		OneOut, 
		TwoOuts,
		ThreeOuts,
		Unknown,
	};
}

//enum to store the current flyball tendency
UENUM(BlueprintType)
namespace EYOFlyBallTendency
{
	enum Type
	{
		VeryLow,
		Low,
		Medium,
		High,
		VeryHigh,
		Unknown,
	};
}



/**
 * Yer Out Baseball game mode class
 */
UCLASS()
class YEROUTBASEBALL_API AYOGameMode : public AGameMode
{
	GENERATED_UCLASS_BODY()
	
public:
	//Get the current state in the game
	UFUNCTION(BlueprintCallable, Category = Baseball)
	EYOGameState::Type GetCurrentState() const;
	
	//Sets the current state enum
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void SetCurrentState(EYOGameState::Type NewState);

	//Gets the struct for the current batter
	FCurrentBatter GetCurrentBatter() const;

	//Sets the current batter
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void SetCurrentBatter(FCurrentBatter NewBatter);

	//Gets the struct for the current pitcher
	FCurrentPitcher GetCurrentPitcher() const;

	//Sets the current pitcher
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void SetCurrentPitcher(FCurrentPitcher NewPitcher);

	//Gets the struct for the ball in play
	FBallInPlay GetBallInPlay() const;

	//Sets the ball in play struct
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void SetBallInPlay(FBallInPlay NewBallInPlay);

	//Gets the struct for the batting and fielding teams current strategies.
	FCoachStrategy GetStrategy() const;

	//Sets the current pitcher
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void SetStrategy(FCoachStrategy NewStrategy);

	//Gets the struct for the current base paths info.
	UFUNCTION(BlueprintCallable, Category = Baseball)
	FCurrentBaseStates GetBasePathStates() const;

	//Sets the new base path info
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void SetBasePathState(FCurrentBaseStates NewBaseState);

	//Logging array variable
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	TArray<FString> BaseballSimLog;

	EYOOuts::Type GetCurrentOuts() const;

	//Sets outs
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void SetOuts(EYOOuts::Type NewOuts);

	//Sets outs
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void IncrementNumberOfOuts();

	//TEMP SCORE HOLDER - DELETE ME 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	int32 TempScore;

	//Display Log
	void BaseballSimLogging();

	virtual void BeginPlay() override;

private:
	//State of the game variable
	EYOGameState::Type CurrentState;

	//Current outs
	EYOOuts::Type Outs;



	//Handles the new states
	void HandleNewStates(EYOGameState::Type NewState);

	//The current player at bat (the batter)
	FCurrentBatter CurrentBatter;

	//The current pitching who's pitching.
	FCurrentPitcher CurrentPitcher;

	//Data to be used for determining if the batter gets on base as well as any fielding errors.
	FBallInPlay TheBallIsInPlay;

	//Struct to hold the home and visiting team strategies
	FCoachStrategy Strategy;

	//Information about the bases
	FCurrentBaseStates CurrentBaseState;

	//This is where the game is being played at.
	FBallPark BallPark;
	
};


FORCEINLINE EYOGameState::Type AYOGameMode::GetCurrentState() const
{
	return CurrentState;
}

FORCEINLINE FCurrentBatter AYOGameMode::GetCurrentBatter() const
{
	return CurrentBatter;
}

FORCEINLINE FCurrentPitcher AYOGameMode::GetCurrentPitcher() const
{
	return CurrentPitcher;
}

FORCEINLINE FCoachStrategy AYOGameMode::GetStrategy() const
{
	return Strategy;
}

FORCEINLINE FBallInPlay AYOGameMode::GetBallInPlay() const
{
	return TheBallIsInPlay;
}

FORCEINLINE FCurrentBaseStates  AYOGameMode::GetBasePathStates() const
{
	return CurrentBaseState;
}

FORCEINLINE EYOOuts::Type AYOGameMode::GetCurrentOuts() const
{
	return Outs;
}
