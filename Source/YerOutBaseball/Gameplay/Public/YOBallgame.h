// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
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

private:

};
