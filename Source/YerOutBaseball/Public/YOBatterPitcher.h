// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "YerOutBaseball.h"
#include "YOBatterPitcher.generated.h"



/**
* Struct that holds the information for the player that is currently batting.
*/
USTRUCT(BlueprintType)
struct FCurrentBatter
{
	GENERATED_USTRUCT_BODY()

	FCurrentBatter()
	: BatterName(TEXT("Unknown"))
	, ID(NULL)
	, LineupOrderNumber(0)
	, Contact(500)
	, Eye(500)
	, SCLeft(33)
	, SCCenter(34)
	, SCRight(33)
	, BatterFlyballTendency(2)
	, Power(350)
	, BatHand("R")
	{}

	//Batter Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	FString BatterName;

	//Batter ID number
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	int32 ID;

	//Batters Order in the lineup 1-9
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	int32 LineupOrderNumber;

	//Contact - The ability to hit the ball into play.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	int32 Contact;

	//Eye - The ability to get on base when not making contact (e.g. a walk).
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	int32 Eye;

	//Spray Chart - What part of the field does the batter hit it to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	float SCLeft;

	//Spray Chart - What part of the field does the batter hit it to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	float SCCenter;

	//Spray Chart - What part of the field does the batter hit it to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	float SCRight;

	//Likelyhood of a fly ball
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	uint8 BatterFlyballTendency;

	//Power - The distance in which the batter can hit the ball.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	int32 Power;

	//Bat Hand
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	FString BatHand;
};

/**
* Struct that holds the information for the player that is currently pitching.
*/
USTRUCT(BlueprintType)
struct FCurrentPitcher
{
	GENERATED_USTRUCT_BODY()

	//Pitcher Name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	FString PitcherName;

	//Player ID number
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	int32 ID;

	//Pitcher throw hand
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	FString ThrowHand;

	//Pitcher Top Pitch Speed
	//Affects - Batter Spray Locations, Pitchers Opponents Contact, basestealers?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	int32 PitchSpeedFastest;

	//Pitcher slowest Pitch Speed
	//Affects - Batter Spray Locations, Pitchers Opponents Contact, basestealers?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	int32 PitchSpeedSlowest;
	
	//Pitchers ability to move the ball while thrown
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	int32 PitchMovement;

	//Pitchers ability to 'hit their spots'.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	int32 PitchControl;

	//Pitchers tendency to get either a groundball or a flyball
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	uint8 FlyBallTendency;
};
