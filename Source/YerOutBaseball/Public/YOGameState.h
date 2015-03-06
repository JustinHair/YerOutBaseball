// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "YOGameMode.h"
#include "YOBatterPitcher.h"
#include "YORunningAndFielding.h"
#include "YOBallParks.h"
#include "YOGameState.generated.h"

/**
 * 
 */
UCLASS()
class YEROUTBASEBALL_API AYOGameState : public AGameState
{
	GENERATED_BODY()
public:
	//This function determines if the ball was put into play during a duel between the batter and the pitcher.
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void DetermineIfBallBattedIntoPlay(FCurrentBatter& InCurrentBatter, FCurrentPitcher& InCurrentPitcher);

	//Uses the batters spray chart to determine which part of the field he hit it too.
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void BattedBallLocation(FCurrentBatter& InCurrentBatter, FCurrentPitcher& InCurrentPitcher, FBallInPlay& InBallInPlay);

	//Determines how hard the ball was hit.
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void BattedBallDistance(FCurrentBatter& InCurrentBatter, FBallInPlay& InBallInPlay, const FCoachStrategy& InStrategy);

	//Determines the type of hit (fly ball, line drive, or a ground ball)
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void BattedBallType(FCurrentBatter& InCurrentBatter, FCurrentPitcher& InCurrentPitcher, FBallInPlay& InBallInPlay);

	//Is the batter being intentionally walked?
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void DetermineIfIBB(FCurrentBatter& InCurrentBatter, const FCoachStrategy& InStrategy, FCurrentBaseStates& InCurrentBaseState);

	//Determine if the batter is walked
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void DetermineIfBatterWalked(FCurrentBatter& InCurrentBatter, FCurrentPitcher& InCurrentPitcher, FCurrentBaseStates& InCurrentBaseState);

	//Batter Strikes out
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void BatterStruckOut();

	//Determine if the batter bunts
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void DetermineIfBatterBunts(const FCurrentBatter& InCurrentBatter, const FCoachStrategy& InStrategy);

	//Determine if the batter hits a homerun
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void DetermineIfHomerun(const FBallInPlay& InBallInPlay, const FCoachStrategy& InStrategy, const FBallPark& InBallPark, FCurrentBaseStates& InCurrentBaseState);

	//Determine if the batter hits a homerun
	UFUNCTION(BlueprintCallable, Category = Baseball)
	void DetermineIfFielderCanGetToTheBall();

	void PlayResolution(FBallInPlay& InHitBallDistance, FCurrentBaseStates& InCurrentBaseState);

	UFUNCTION(BlueprintCallable, Category = Baseball)
	AYOGameMode* GetCurrentGameMode() const;

	//====VARIABLES=======//
	//Inning Count
	float CurrentInning = 0;
	//Temp Current Pitch Speed
	int32 CurrentPitchSpeed;
	//Total Scores
	int32 HomeTeamScore = 0;
	int32 VisitingTeamScore = 0;



private:
	AYOGameMode* CurrentGameMode = Cast<AYOGameMode>(UGameplayStatics::GetGameMode(this));

	bool IsHomeRun(const int32& InBallDistance, const int32& InWallDistance, const int32 InWallHeight, const bool& bIsALineDrive);
};

FORCEINLINE AYOGameMode* AYOGameState::GetCurrentGameMode() const
{
	return CurrentGameMode;
}
