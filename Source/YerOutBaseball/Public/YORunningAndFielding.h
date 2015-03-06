//copyright stuff

#pragma once

#include "YerOutBaseball.h"
#include "YOBatterPitcher.h"
#include "YORunningAndFielding.generated.h"

/**
* Struct that holds various info in regards to a baseball being hit into play.
*/
USTRUCT(BlueprintType)
struct FBallInPlay
{
	GENERATED_USTRUCT_BODY()

public:
	FBallInPlay()
		: BallHitToLeft(false)
		, BallHitToLeftCenter(false)
		, BallHitToCenter(false)
		, BallHitToRightCenter(false)
		, BallHitToRight(false)
		, HitBallDistance(0)
		, bIsAFlyBall(false)
		, bIsAGroundBall(false)
	{}


	//Hit Location of the ball
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	bool BallHitToLeft;

	//Hit Location of the ball
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	bool BallHitToLeftCenter;

	//Hit Location of the ball
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	bool BallHitToCenter;

	//Hit Location of the ball
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	bool BallHitToRightCenter;

	//Hit Location of the ball
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	bool BallHitToRight;

	//Reset ball hit location
	void ResetBallHitLocations()
	{
		BallHitToLeft = false;
		BallHitToLeftCenter = false;
		BallHitToCenter = false;
		BallHitToRightCenter = false;
		BallHitToRight = false;
	}

	//The distance in feet the ball can potentially travel.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	int32 HitBallDistance;

	//true if the ball is hit as a fly ball.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	bool bIsAFlyBall;

	//true if the ball is a ground drive.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	bool bIsAGroundBall;

	//Reset the ball in flight height
	void ResetBallHitHeight()
	{
		bIsAFlyBall = false;
		bIsAGroundBall = false;
	}

};

/**
* Struct that holds the strategy that each team will use per at bat.
*/
USTRUCT(BlueprintType)
struct FCurrentBaseRunner
{
	GENERATED_USTRUCT_BODY()

public:
	FCurrentBaseRunner()
		: BaseRunnerName(TEXT("Unknown"))
		, ID(NULL)
		, CurrentOccupiedBase(0)
		, bIsRunnerValid(true)
		, bIsRunnerScored(false)
	{}
	//Base runner name
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
		FString BaseRunnerName;

	//Batter ID
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
		int32 ID;

	//Which base does this player occupy. (0-4, 0 == Not Set, 4 == home plate)
	uint8 CurrentOccupiedBase;

	//Is the runner valid to use.
	//An invalid runner will not be used.  Need to be reset to default.
	bool bIsRunnerValid;

	//An invalid runner will not be used.  Need to be reset to default.
	bool bIsRunnerScored;

};


/**
* Struct that holds the information for the runners on the base paths.
*/
USTRUCT(BlueprintType)
struct FCurrentBaseStates
{
	GENERATED_USTRUCT_BODY()

public:
	FCurrentBaseStates()
		: bIs1BOccupied(false)
		, bIs2BOccupied(false)
		, bIs3BOccupied(false)
		, RunnerA()
		, RunnerB()
		, RunnerC()
		, RunnerD()
	{}
	//Is first base occupied
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	bool bIs1BOccupied;

	//Is second base occupied
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	bool bIs2BOccupied;

	//Is third base occupied
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	bool bIs3BOccupied;

	//clear Occupied bases
	void ResetAllBases()
	{
		bIs1BOccupied = false;
		bIs2BOccupied = false;
		bIs3BOccupied = false;
	}

	void SetOccupiedBases()
	{
		for (uint8 i = 0; i < RunnerSlots.Num(); i++)
		{
			if (RunnerSlots[i].CurrentOccupiedBase == 1)
			{
				bIs1BOccupied = true;
			}
			else if (RunnerSlots[i].CurrentOccupiedBase == 2)
			{
				bIs2BOccupied = true;
			}
			else if (RunnerSlots[i].CurrentOccupiedBase == 3)
			{
				bIs3BOccupied = true;
			}
		}
	}

	//Base Runners
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	FCurrentBaseRunner RunnerA;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	FCurrentBaseRunner RunnerB;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	FCurrentBaseRunner RunnerC;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	FCurrentBaseRunner RunnerD;

	TArray<FCurrentBaseRunner> RunnerSlots;

	//function that resets the runners to their defaults.
	void ResetInvalidRunnerSlots()
	{
		for (uint8 i = 0; i < RunnerSlots.Num(); i++)
		{
			if (!RunnerSlots[i].bIsRunnerValid)
			{
				//Make sure the runners old base is set to false.
				if (RunnerSlots[i].CurrentOccupiedBase == 1)
				{
					bIs1BOccupied = false;
				}
				else if (RunnerSlots[i].CurrentOccupiedBase == 2)
				{
					bIs2BOccupied = false;
				}
				else if (RunnerSlots[i].CurrentOccupiedBase == 3)
				{
					bIs3BOccupied = false;
				}

				RunnerSlots[i].BaseRunnerName = (TEXT("Unknown"));
				RunnerSlots[i].ID = NULL;
				RunnerSlots[i].CurrentOccupiedBase = 0;
				RunnerSlots[i].bIsRunnerValid = true;
				RunnerSlots[i].bIsRunnerScored = false;
			}
		}
	}

	void ResetAllRunnerSlots()
	{
		for (uint8 i = 0; i < RunnerSlots.Num(); i++)
		{
			RunnerSlots[i].BaseRunnerName = (TEXT("Unknown"));
			RunnerSlots[i].ID = NULL;
			RunnerSlots[i].CurrentOccupiedBase = 0;
			RunnerSlots[i].bIsRunnerValid = true;
			RunnerSlots[i].bIsRunnerScored = false;
		}
	}

	//Convert the batter into a baserunner.
	void ConvertBatterToBaseRunner(const FCurrentBatter& InBatter)
	{
		for (uint8 i = 0; i < RunnerSlots.Num(); i++)
		{

			if (RunnerSlots[i].CurrentOccupiedBase == 0)
			{
				RunnerSlots[i].BaseRunnerName = InBatter.BatterName;
				RunnerSlots[i].ID = InBatter.ID;
				RunnerSlots[i].CurrentOccupiedBase = 0;
				return;
			}
		}
		UE_LOG(YOLOG, Warning, TEXT("No open runner slots"));
	}

	//Add to the scoreboard if any of the runner slots are four or greater.
	int32 ScoreRunners()
	{
		int32 RunScored = 0;
		for (uint8 i = 0; i < RunnerSlots.Num(); i++)
		{
			if (RunnerSlots[i].bIsRunnerScored && RunnerSlots[i].bIsRunnerValid && RunnerSlots[i].ID != NULL)
			{
				RunnerSlots[i].bIsRunnerValid = false;
				RunScored++;
			}
		}
		return RunScored;
	}

	//Get the player ID for a runner on a specific base.
	//@param InBaseNumber - number that represents a base.  1 == first base, 3 == 3rd base
	int32 GetRunnerID(const uint8& InBaseNumber)
	{
		for (uint8 i = 0; i < RunnerSlots.Num(); i++)
		{
			if (RunnerSlots[i].CurrentOccupiedBase == InBaseNumber)
			{
				return RunnerSlots[i].ID;
			}
		}
		return NULL;
	}

	/** Advance all runners. */
	void AdvanceAllBaseRunners(const int32& InAdvancingNumber)
	{
		for (uint8 i = 0; i < RunnerSlots.Num(); i++)
		{
			if (RunnerSlots[i].ID > 0)
			{
				RunnerSlots[i].CurrentOccupiedBase += InAdvancingNumber;
				if (RunnerSlots[i].CurrentOccupiedBase >= 4 && RunnerSlots[i].bIsRunnerValid)
				{
					RunnerSlots[i].bIsRunnerScored = true;
				}
			}
		}
		SetOccupiedBases();
	}

	/** Advance all runners that can be forced out by one base. */
	void AdvanceAllForceableRunners()
	{
		if (!bIs1BOccupied)
		{
			for (uint8 i = 0; i < RunnerSlots.Num(); i++)
			{
				if (RunnerSlots[i].CurrentOccupiedBase == 0 && RunnerSlots[i].ID > 0)
				{
					RunnerSlots[i].CurrentOccupiedBase = 1;
					SetOccupiedBases();
					return;
				}
			}
		}
		//If the bases are loaded then we just move all of the runners.
		if ((bIs1BOccupied && bIs2BOccupied && bIs3BOccupied) || (bIs1BOccupied && bIs2BOccupied))
		{
			AdvanceAllBaseRunners(1);
			return;
		}
		if (bIs1BOccupied)
		{
			for (uint8 i = 0; i < RunnerSlots.Num(); i++)
			{
				if ((RunnerSlots[i].CurrentOccupiedBase < 2 && RunnerSlots[i].ID > 0))
				{
					RunnerSlots[i].CurrentOccupiedBase++;
					SetOccupiedBases();
					return;
				}
			}
		}
	}

	/** Advance the base runner
	* @param InRunnerID - The player ID of the desired runner.
	* @param InAdvancingNumber - The number of bases the player is advancing
	*/
	void AdvanceBaseRunner(const int32& InRunnerID, const int32& InAdvancingNumber)
	{
		for (uint8 i = 0; i < RunnerSlots.Num(); i++)
		{
			RunnerSlots[i].CurrentOccupiedBase += InAdvancingNumber;

			if (RunnerSlots[i].ID == InRunnerID)
			{
				//Score the runner if the new position is home plate (4 or greater)
				if (RunnerSlots[i].CurrentOccupiedBase >= 4)
				{
					bIs3BOccupied = false;
				}
				else if (RunnerSlots[i].CurrentOccupiedBase == 3 && !bIs3BOccupied)
				{
					bIs2BOccupied = false;
					bIs3BOccupied = true;
				}
				else if (RunnerSlots[i].CurrentOccupiedBase == 2 && !bIs2BOccupied)
				{
					bIs1BOccupied = false;
					bIs2BOccupied = true;
				}
				else if (RunnerSlots[i].CurrentOccupiedBase == 1 && !bIs1BOccupied)
				{
					bIs1BOccupied = true;
				}
				if (RunnerSlots[i].CurrentOccupiedBase <= 0)
				{
					UE_LOG(YOLOG, Error, (TEXT("All bases are occupied, something is wrong!")));
				}
				SetOccupiedBases();
				return;
			}
		}
	}

};




/**
* Struct that holds the strategy that each team will use per at bat.
*/
USTRUCT(BlueprintType)
struct FCoachStrategy
{
	GENERATED_USTRUCT_BODY()

public:
	FCoachStrategy()
		: bIsIBB(false)
		, bIsBunting(false)
	{}

	//intentionally walking a batter variable.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	bool bIsIBB;

	//Force the batter to bunt
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
	bool bIsBunting;

	//Work the pitch count

	//Steal
};
