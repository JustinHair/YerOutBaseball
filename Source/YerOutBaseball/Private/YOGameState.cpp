// Fill out your copyright notice in the Description page of Project Settings.

#include "YerOutBaseball.h"
#include "YOGameState.h"
#include "YOGameMode.h"
#include "YOBatterPitcher.h"
#include "YORunningAndFielding.h"

//To get the current game mode.
#include "Kismet/GameplayStatics.h"

//defines
#define AVG_LINE_DRIVE_RATE				19.87
#define RAND_RANGE_MAX					1000.0f


int32 FlyBallAdjustment(const uint8& InFlyBallAttribute)
{
	int32 FlyBallChange = InFlyBallAttribute;

	if (InFlyBallAttribute < 0)
	{
		FlyBallChange = 0;
	}
	else if (InFlyBallAttribute > 4)
	{
		FlyBallChange = 4;
	}

	return (FlyBallChange - 2);
}


void AYOGameState::DetermineIfBallBattedIntoPlay(FCurrentBatter& InCurrentBatter, FCurrentPitcher& InCurrentPitcher)
{
	if (CurrentGameMode->GetCurrentState() == EYOGameState::AtBatInProgress)
	{
		//Adjust the batter ability to hit the ball based against the pitchers ability to miss bats.
		float CombinedBatterPitcherAttributes = InCurrentBatter.Contact + (InCurrentPitcher.PitchControl + InCurrentPitcher.PitchMovement);
		float AdjustedContact = RAND_RANGE_MAX * (CombinedBatterPitcherAttributes / 2000);

		//Now we adjust the new contact number by subtracting the speed of the pitch from it.  The faster the speed the less likely the batter will hit the ball.
		//InCurrentPitcher.InCurrentPitchSpeed = FMath::RandRange(InCurrentPitcher.PitchSpeedSlowest, InCurrentPitcher.PitchSpeedFastest);
		CurrentPitchSpeed = FMath::RandRange(InCurrentPitcher.PitchSpeedSlowest, InCurrentPitcher.PitchSpeedFastest);
		AdjustedContact -= CurrentPitchSpeed;

		float RandomRange = FMath::RandRange(1, RAND_RANGE_MAX);

		//The ball is hit into play when the random range number is less than the adjusted on base ability.
		if (RandomRange < AdjustedContact)
		{
			CurrentGameMode->SetCurrentState(EYOGameState::BallInPlay);
		}
	}
}

void AYOGameState::BattedBallLocation(FCurrentBatter& InCurrentBatter, FCurrentPitcher& InCurrentPitcher, FBallInPlay& InBallInPlay)
{
	if (CurrentGameMode->GetCurrentState() == EYOGameState::BallInPlay)
	{
		//set the ball hit locations to false.
		InBallInPlay.ResetBallHitLocations();

		//Compare the batter and pitchers hands (lefty vs Right, etc.)
		//Then adjust batters spray charts based on the pitchers pitch speed variable.	
		//The theory is that if the pitcher throws fast then the batter will be slow to swing causing his hits to go to the opposite field more often.
		float AdjustByPitchSpeed = CurrentPitchSpeed / 10.f;
		float NewSCLeft = InCurrentBatter.SCLeft;
		float NewSCCenter = InCurrentBatter.SCCenter + (AdjustByPitchSpeed / 2);
		float NewSCRight = InCurrentBatter.SCRight;
		float SCLeftCenter = 0;
		float SCRightCenter = 0;

		//Right handed batter or for a switch hitter vs a left hand pitcher or a switch handed pitcher
		if ((InCurrentBatter.BatHand == "R") || (InCurrentBatter.BatHand == "S" && InCurrentPitcher.ThrowHand == "L") || (InCurrentBatter.BatHand == "S" && InCurrentPitcher.ThrowHand == "S"))
		{
			NewSCRight += AdjustByPitchSpeed;
			SCLeftCenter = (NewSCLeft + NewSCCenter) / 2;
			SCRightCenter = (NewSCRight + NewSCCenter) / 2;

			float CombinedSCValue = (NewSCLeft + SCLeftCenter + NewSCCenter + SCRightCenter + NewSCRight);
			float RandomHitLocationRange = FMath::RandRange(1, CombinedSCValue);


			//Will the ball be hit to the right side of the field.
			if (RandomHitLocationRange < NewSCRight)
			{
				InBallInPlay.BallHitToRight = true;
				CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("That was knocked to the 'right' side of the diamond.\n")));
				return;
			}
			else if (RandomHitLocationRange < (NewSCRight + SCRightCenter))
			{
				InBallInPlay.BallHitToRightCenter = true;
				CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("That was knocked to 'right center'.\n")));
				return;
			}
			else if (RandomHitLocationRange < (NewSCRight + SCRightCenter + NewSCCenter))
			{
				InBallInPlay.BallHitToCenter = true;
				CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("That was knocked to 'center' of the diamond.\n")));
				return;
			}
			else if (RandomHitLocationRange < (NewSCRight + SCRightCenter + NewSCCenter + SCLeftCenter))
			{
				InBallInPlay.BallHitToLeftCenter = true;
				CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("That was knocked to the 'left Center'.\n")));
				return;
			}
			else
			{
				InBallInPlay.BallHitToLeft = true;
				CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("That was knocked to 'left' side of the diamond.\n")));
				return;
			}
		}
		else
		{
			NewSCLeft += AdjustByPitchSpeed;
			SCLeftCenter = (NewSCLeft + NewSCCenter) / 2;
			SCRightCenter = (NewSCRight + NewSCCenter) / 2;

			float CombinedSCValue = (NewSCLeft + SCLeftCenter + NewSCCenter + SCRightCenter + NewSCRight);
			float RandomHitLocationRange = FMath::RandRange(1, CombinedSCValue);

			//Will the ball be hit to the Left side of the field.
			if (RandomHitLocationRange < NewSCLeft)
			{
				InBallInPlay.BallHitToLeft = true;
				CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("That was knocked to the 'left' side of the diamond.\n")));
				return;
			}
			else if (RandomHitLocationRange < (NewSCLeft + SCRightCenter))
			{
				InBallInPlay.BallHitToLeftCenter = true;
				CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("That was knocked to 'left center'.\n")));
				return;
			}
			else if (RandomHitLocationRange < (NewSCLeft + SCLeftCenter + NewSCCenter))
			{
				InBallInPlay.BallHitToCenter = true;
				CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("That was knocked to 'center' of the diamond.\n")));
				return;
			}
			else if (RandomHitLocationRange < (NewSCLeft + SCLeftCenter + NewSCCenter + SCRightCenter))
			{
				InBallInPlay.BallHitToRightCenter = true;
				CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("That was knocked to the 'right Center'.\n")));
				return;
			}
			else
			{
				InBallInPlay.BallHitToRight = true;
				CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("That was knocked to 'right' side of the diamond.\n")));
				return;
			}
		}
	}
}

void AYOGameState::BattedBallDistance(FCurrentBatter& InCurrentBatter, FBallInPlay& InBallInPlay, const FCoachStrategy& InStrategy)
{
	if (CurrentGameMode->GetCurrentState() == EYOGameState::BallInPlay)
	{
		//The strength of the hit is determined by the the batters power which is then adjusted based on the pitchers pitch speed.
		//The faster the pitch the harder it will be hit.
		float HitDistance = FMath::FRandRange(1, InCurrentBatter.Power) + CurrentPitchSpeed;
		if (InStrategy.bIsBunting)
		{
			HitDistance = FMath::FRandRange(1, (InCurrentBatter.Power/5)) + (CurrentPitchSpeed/10);
		}

		InBallInPlay.HitBallDistance = HitDistance;

		CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("It had an estimated distance of %i feet.\n"), InBallInPlay.HitBallDistance));
	}
}

void AYOGameState::BattedBallType(FCurrentBatter& InCurrentBatter, FCurrentPitcher& InCurrentPitcher, FBallInPlay& InBallInPlay)
{
	if (CurrentGameMode->GetCurrentState() == EYOGameState::BallInPlay)
	{
		InBallInPlay.ResetBallHitHeight();

		//Determine if the batter hit a line drive
		if (FMath::RandRange(1, 100) <= AVG_LINE_DRIVE_RATE)
		{
			CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("%s lines one out.\n"), *InCurrentBatter.BatterName));
			return;
		}

		//If the batter didn't hit a line drive then we'll determine if the ball was either a grounder or a fly ball.
		//Sets the batter and pitcher flyball tendencies to be in a valid range.
		//Gets the change that will occur to the default flyball tendency.
		int32 BatterFlyBallChange = FlyBallAdjustment(InCurrentBatter.BatterFlyballTendency);
		int32 PitcherFlyBallChange = FlyBallAdjustment(InCurrentPitcher.FlyBallTendency);
		int32 ActualFlyBallTendency = 5 + BatterFlyBallChange + PitcherFlyBallChange;
	
		float RandomRange = FMath::RandRange(1, 10);
		if (RandomRange <= ActualFlyBallTendency)
		{
			InBallInPlay.bIsAFlyBall = true;
			CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("%s pops one into the air.\n"), *InCurrentBatter.BatterName));
			return;
		}
		else
		{
			InBallInPlay.bIsAGroundBall = true;
			CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("%s bounces one into the field.\n"), *InCurrentBatter.BatterName));
		}     
	}
}

void AYOGameState::DetermineIfIBB(FCurrentBatter& InCurrentBatter, const FCoachStrategy& InStrategy, FCurrentBaseStates& InCurrentBaseState)
{
	if (CurrentGameMode->GetCurrentState() == EYOGameState::AtBatInProgress)
	{
		if (InStrategy.bIsIBB)
		{
			//Convert the batter to a base runner
			InCurrentBaseState.ConvertBatterToBaseRunner(InCurrentBatter);
			InCurrentBaseState.AdvanceAllForceableRunners();

			CurrentGameMode->SetCurrentState(EYOGameState::PlayResolution);
			return;
		}
	}
}

void AYOGameState::DetermineIfBatterWalked(FCurrentBatter& InCurrentBatter, FCurrentPitcher& InCurrentPitcher, FCurrentBaseStates& InCurrentBaseState)
{
	if (CurrentGameMode->GetCurrentState() == EYOGameState::AtBatInProgress)
	{
		//((BatterEye*(pitcherControl))+BatterEye)/(PitcherMovement + (1000-BatterEye))
		int32 WalkRate = ((InCurrentBatter.Eye * (InCurrentPitcher.PitchControl)) + InCurrentBatter.Eye) / (InCurrentPitcher.PitchMovement + (1000 - InCurrentBatter.Eye));
		float RandomRange = FMath::RandRange(1, 100);

		if (RandomRange <= WalkRate)
		{
			//Convert the batter to a base runner
			InCurrentBaseState.ConvertBatterToBaseRunner(InCurrentBatter);

			//If first base is not being occupied by another runner then put the batter there.
			InCurrentBaseState.AdvanceAllForceableRunners();

			CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("%s walks."), *InCurrentBatter.BatterName));
			CurrentGameMode->SetCurrentState(EYOGameState::PlayResolution);
			return;
		}
	}
}

void AYOGameState::BatterStruckOut()
{
	if (CurrentGameMode->GetCurrentState() == EYOGameState::AtBatInProgress)
	{
		CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("Struck out.")));
		CurrentGameMode->IncrementNumberOfOuts();
		CurrentGameMode->SetCurrentState(EYOGameState::PlayResolution);
	}
}

void AYOGameState::DetermineIfBatterBunts(const FCurrentBatter& InCurrentBatter, const FCoachStrategy& InStrategy)
{
	if (CurrentGameMode->GetCurrentState() == EYOGameState::AtBatInProgress)
	{
		if (InStrategy.bIsBunting)
		{
			float RandomRange = FMath::RandRange(1, RAND_RANGE_MAX);

			//The ball is hit into play when the random range number is less than the adjusted on base ability.
			if (RandomRange < InCurrentBatter.Contact)
			{
				CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("%s bunts the ball."), *InCurrentBatter.BatterName));
				CurrentGameMode->SetCurrentState(EYOGameState::BallInPlay);
			}
		}
	}
}

bool AYOGameState::IsHomeRun(const int32& InBallDistance, const int32& InWallDistance, const int32 InWallHeight, const bool& bIsALineDrive)
{
	if (InBallDistance > InWallDistance)
	{
		if (InWallDistance == 0)
		{
			//Zero means that there isn't an outfield wall.
			CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("That ball is going to roll forever!")));
			return false;
		}
		else if (!bIsALineDrive)
		{
			return true;
		}
		else if (bIsALineDrive && ((InBallDistance > (InWallDistance + InWallHeight))))
		{
			return true; 
		}
	}
	return false;
}

void AYOGameState::DetermineIfHomerun(const FBallInPlay& InBallInPlay, const FCoachStrategy& InStrategy, const FBallPark& InBallPark, FCurrentBaseStates& InCurrentBaseState)
{
	if (CurrentGameMode->GetCurrentState() == EYOGameState::BallInPlay)
	{
		//A homerun can only be hit when the batter is not bunting.
		if (!InStrategy.bIsBunting && !InBallInPlay.bIsAGroundBall)
		{
			//temp variables that will hold whether or not a hit is a homerun
			bool bIsLHR		=	false;
			bool bIsLCHR	=	false;
			bool bIsCHR		=	false;
			bool bIsRCHR	=	false;
			bool bIsRHR		=	false;

			//if the hit is a fly ball and it's greater than the fence then it's a homerun.
			if (InBallInPlay.bIsAFlyBall)
			{
				bIsLHR		=	(IsHomeRun(InBallInPlay.HitBallDistance, InBallPark.LeftFieldWallDistance, InBallPark.LeftFieldWallHeight, false) && InBallInPlay.BallHitToLeft);
				bIsLCHR		=	(IsHomeRun(InBallInPlay.HitBallDistance, InBallPark.LeftCenterWallDistance, InBallPark.LeftCenterWallHeight, false) && InBallInPlay.BallHitToLeftCenter);
				bIsCHR		=	(IsHomeRun(InBallInPlay.HitBallDistance, InBallPark.CenterWallDistance, InBallPark.CenterWallHeight, false) && InBallInPlay.BallHitToCenter);
				bIsRCHR		=	(IsHomeRun(InBallInPlay.HitBallDistance, InBallPark.RightCenterWallDistance, InBallPark.RightCenterWallHeight, false) && InBallInPlay.BallHitToRightCenter);
				bIsRHR		=	(IsHomeRun(InBallInPlay.HitBallDistance, InBallPark.RightFieldWallDistance, InBallPark.RightFieldWallHeight, false) && InBallInPlay.BallHitToRight);
				if (bIsLHR || bIsLCHR || bIsCHR || bIsRCHR || bIsRHR)
				{
					InCurrentBaseState.AdvanceAllBaseRunners(4);
					CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("\nHOMERUN!!\n")));
					CurrentGameMode->SetCurrentState(EYOGameState::PlayResolution);
				}
			}
			else
			{
				//If a line drive is hit deep enough it too can be a homerun.  
				//Line drives have to travel the distance of the wall plus an additional amount that equals the height of the wall.
				bIsLHR		=	(IsHomeRun(InBallInPlay.HitBallDistance, InBallPark.LeftFieldWallDistance, InBallPark.LeftFieldWallHeight, true) && InBallInPlay.BallHitToLeft);
				bIsLCHR		=	(IsHomeRun(InBallInPlay.HitBallDistance, InBallPark.LeftCenterWallDistance, InBallPark.LeftCenterWallHeight, true) && InBallInPlay.BallHitToLeftCenter);
				bIsCHR		=	(IsHomeRun(InBallInPlay.HitBallDistance, InBallPark.CenterWallDistance, InBallPark.CenterWallHeight, true) && InBallInPlay.BallHitToCenter);
				bIsRCHR		=	(IsHomeRun(InBallInPlay.HitBallDistance, InBallPark.RightCenterWallDistance, InBallPark.RightCenterWallHeight, true) && InBallInPlay.BallHitToRightCenter);
				bIsRHR		=	(IsHomeRun(InBallInPlay.HitBallDistance, InBallPark.RightFieldWallDistance, InBallPark.RightFieldWallHeight, true) && InBallInPlay.BallHitToRight);
				if (bIsLHR || bIsLCHR || bIsCHR || bIsRCHR || bIsRHR)
				{
					InCurrentBaseState.AdvanceAllBaseRunners(4);
					CurrentGameMode->BaseballSimLog.Add(FString::Printf(TEXT("\nLine drive HOMERUN!!\n")));
					CurrentGameMode->SetCurrentState(EYOGameState::PlayResolution);
				}
			}
		}
	}
}

void AYOGameState::DetermineIfFielderCanGetToTheBall()
{

}

void AYOGameState::PlayResolution(FBallInPlay& InBallInPlayStruct, FCurrentBaseStates& InCurrentBaseState)
{
	if (CurrentGameMode->GetCurrentState() == EYOGameState::PlayResolution)
	{
		CurrentGameMode->TempScore += InCurrentBaseState.ScoreRunners();

		InCurrentBaseState.ResetInvalidRunnerSlots();

		//This should reset All only after 3 outs.
		//InCurrentBaseState.ResetAllBases();
		//ResetAllRunnerSlots();
		
	}
}

