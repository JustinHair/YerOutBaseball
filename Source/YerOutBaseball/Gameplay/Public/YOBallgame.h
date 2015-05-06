// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

/**
 * Class used for simulating a baseball game.
 */
class YEROUTBASEBALL_API YOBallgame
{
public:
	YOBallgame();
	~YOBallgame();



	//***** STRATEGY *****/
	//Determine if the fielding team is going to intentionally walk the batter.
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
	/*
	**Set the game state to the desired state.
	**@NewGameState - Enum which will be used by the game state.
	*/
	void SetGameState(EYOGameState::Type NewGameState);

	//returns the current game state as an enum.
	EYOGameState::Type GetCurrentGameState() const;

private:
	//Switches the game state when it is changed.
	void HandleNewStates(EYOGameState::Type NewState);
	
	EYOGameState::Type CurrentGameState;

};
