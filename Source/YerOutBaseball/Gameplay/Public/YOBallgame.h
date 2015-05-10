// Fill out your copyright notice in the Description page of Project Settings.

#include "YOBallGame.generated.h"
#pragma once

//enum to store the current state of the game.
UENUM(BlueprintType)
namespace EYOGameStatex
{
	enum Type
	{
		InTheMenus,			// Player is in the menus
		PreGame,			// Game processes the line ups
		BeforeThePlay,		// Strategy and attribute changes before the pitcher throws the ball.
		AtBatInProgress,	// Deciding who wins in the battle between pitcher and batter.
		BallInPlay,			// Ball is now in play.
		PlayResolution,		// Move runners, set new outs, capture current game stats
		Unknown,			// ...
	};
}

/**
 * Class used for simulating a baseball game.
 */
UCLASS(BlueprintType, Blueprintable)
class YEROUTBASEBALL_API AYOBallGame : public AInfo
{
	GENERATED_BODY()
public:
	//***** STRATEGY *****/
	//Determine if the fielding team is going to intentionally walk the batter.
	bool IsBatterBeingIntentionallyWalked();
	//Determine if the batter is going to attempt to bunt

	//***** AT BAT IN PROGRESS *****/
	//Is the batter being intentionally walked?
	//Determine if the batter bunts
	//Determine if the ball is batted into play
	//Determine if the batter is walked
	//Determine if the batter struck out.

	//***** BALL IN PLAY *****/
	//Convert Batter to be a baserunner
	//Batted ball type? (ground, line, fly)
	//Batted ball location
	//Batted ball distance
	//Determine if hit is a homerun.

	//***** GAME STATE *****/
	// Returns the current game state enum.
	UFUNCTION(BlueprintCallable, Category = "Baseball|Simulation|Game State")
	EYOGameStatex::Type GetCurrentGameState() const;

	// Set the game state to the desired state.
	// @NewGameState - Enum which will be used by the game state.
	UFUNCTION(BlueprintCallable, Category = "Baseball|Simulation|Game State")
	void SetGameState(EYOGameStatex::Type NewGameState);

	//***** LOGGING *****/
	// Array used to hold the in game logging for the simulation
	TArray<FString> BaseballSimLog;
	// Logs the BaseballSimLog.
	UFUNCTION(BlueprintCallable, Category = "Baseball|Simulation|Logging")
	void PrintBaseballSimLog();

private:
	// Switches the game state when it is changed.
	// @NewState - The state that the game will switch to.
	void HandleNewStates(EYOGameStatex::Type NewState);
	
	// Holds the current game state value.
	EYOGameStatex::Type CurrentGameState;

};
