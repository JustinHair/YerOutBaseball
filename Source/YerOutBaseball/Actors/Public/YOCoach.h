// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//create an enum for stealing
//StraightSteal	<-Force runner to steal
//NoSteal		<-Runner will not run
//HitnRun		<-Runner will steal, batter force to swing, Runner is slower than a straight steal.
//GreenLight	<-Random chance runner will run on his own.
//

//create an enum for batting strategy
//Normal
//Take Pitches
//Agressive

/**
 * 
 */
class YEROUTBASEBALL_API YOCoach
{
public:
	YOCoach();
	~YOCoach();



private:
	//***** GENERAL INFO ******/
	FString Name;

	//***** PREGAME SETUP *****/
	//Line up Creation
	//Starting Pitcher

	//***** PITCHING STRATEGY *****/
	// Intentionally walking the batter
	bool bIsIBBOpposingBatter;

	//***** BATTING STRATEGY ******/
	

	//***** BASERUNNING STRATEGY *****/
	//change this to an enum...
	bool bIsStealing;
};
