// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "YODataTables.generated.h"

/** Structure that defines the positionplayer rating data table entry */
USTRUCT(BlueprintType)
struct FPlayersList : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FPlayersList()
		: PlayerName(TEXT("Default Name"))
		, ID(0)
		, Throw(TEXT("R"))
		, BatHand(TEXT("R"))
		, BatterContact(0)
		, BatterEye(0)
		, BatterPower(0)
		, BatterSprayChartLeft(0)
		, BatterSprayChartCenter(0)
		, BatterSprayChartRight(0)
		, BatterFlyBallTendency(2)
		, PitchSpeedFastest(10)
		, PitchSpeedSlowest(1)
		, PitchMovement(0)
		, PitchControl(0)
		, PitchOppFlyBallTendency(2)
	{}

	/** Players last name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PersonalInfo)
	FString PlayerName;

	/** This is the player ID.  This helps avoid any confusion when players have the same name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerID)
	int32 ID;

	/** Players throwing hand; 'L' (Left) or 'R' (Right) or 'S' (Switch) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PersonalInfo)
	FString Throw;

	/** Players Batting Side; 'L' (Left) or 'R' (Right) or 'S' (Switch) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PersonalInfo)
	FString BatHand;

	/** Players ability to get on base, similar to an OBP stat.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BatterAttributes)
	int32 BatterContact;

	/** Players batting power.  How far can they hit the ball*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BatterAttributes)
	int32 BatterPower;

	/** Players ability to tell a ball from a strike.  The higher the rating the better the chance the batter can get on base after not making contact.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BatterAttributes)
	int32 BatterEye;

	/** Players percentage to hit to left field.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BatterAttributes)
	float BatterSprayChartLeft;

	/** Players percentage to hit to the center of the field.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BatterAttributes)
	float BatterSprayChartCenter;

	/** Players percentage to hit to left field.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BatterAttributes)
	float BatterSprayChartRight;

	/** Players percentage to hit a fly ball.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BatterAttributes)
	uint8 BatterFlyBallTendency;

	/** The fastest speed in MPH the pitch can throw.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PitchAttributes)
	int32 PitchSpeedFastest;

	/** The slowest speed in MPH the pitch can throw.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PitchAttributes)
	int32 PitchSpeedSlowest;

	/** The amount of movement the pitches have while thrown.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PitchAttributes)
	int32 PitchMovement;

	/** The accuracy of the pitch.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PitchAttributes)
	int32 PitchControl;

	/** The opposing batters will typically hit a flyball this often...*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PitchAttributes)
	uint8 PitchOppFlyBallTendency;
};


/** Structure that defines the pitcher player rating data table entry */
USTRUCT(BlueprintType)
struct FPitchersList : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FPitchersList()
		: PlayerName(TEXT("Default Name"))
		, ID(0)
		, Throw(TEXT("R"))
		, PitchControl(100)
		, PitchMovement(300)
		, PitchSpeedFastest(10)
		, PitchSpeedSlowest(1)
		, OpponentFlyballTendency(2)
	{}


	/** Players last name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PersonalInfo)
	FString PlayerName;

	/** This is the player ID.  This helps avoid any confusion when players have the same name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerID)
	int32 ID;

	/** Players throwing hand; 'L' (Left) or 'R' (Right) or 'S' (Switch) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PersonalInfo)
	FString Throw;

	/** The accuracy of the pitch.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PitchAttributes)
	int32 PitchControl;

	/** The amount of movement the pitches have while thrown.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PitchAttributes)
	int32 PitchMovement;

	/** The fastest speed in MPH the pitch can throw.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PitchAttributes)
	int32 PitchSpeedFastest;

	/** The slowest speed in MPH the pitch can throw.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PitchAttributes)
	int32 PitchSpeedSlowest;

	/** The opposing batters will typically hit a flyball this often...*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PitchAttributes)
	uint8 OpponentFlyballTendency;
};


/** Structure that defines the info for a teams ball park */
USTRUCT(BlueprintType)
struct FBallParkInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FBallParkInfo()
		: ParkName(TEXT("Default Name"))
		, ID(0)
		, LeftFieldWallDistance(330)
		, LeftCenterWallDistance(360)
		, CenterWallDistance(405)
		, RightCenterWallDistance(360)
		, RightFieldWallDistance(330)
		, LeftFieldWallHeight(8)
		, LeftCenterWallHeight(8)
		, CenterWallHeight(8)
		, RightCenterWallHeight(8)
		, RightFieldWallHeight(8)
	{}

	/** Ball Park name */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BasicInfo)
	FString ParkName;

	/** This is the ball park ID.  This helps avoid any confusion when ball parks have the same name. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallInfo)
	int32 ID;

	/** The distance from home plate to the outfield wall. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallInfo)
	int32 LeftFieldWallDistance;

	/** The distance from home plate to the outfield wall. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallInfo)
	int32 LeftCenterWallDistance;

	/** The distance from home plate to the outfield wall. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallInfo)
	int32 CenterWallDistance;

	/** The distance from home plate to the outfield wall. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallInfo)
	int32 RightCenterWallDistance;

	/** The distance from home plate to the outfield wall. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallInfo)
	int32 RightFieldWallDistance;

	/** The distance from home plate to the outfield wall. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallInfo)
	int32 LeftFieldWallHeight;

	/** The distance from home plate to the outfield wall. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallInfo)
	int32 LeftCenterWallHeight;

	/** The distance from home plate to the outfield wall. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallInfo)
	int32 CenterWallHeight;

	/** The distance from home plate to the outfield wall. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallInfo)
	int32 RightCenterWallHeight;

	/** The distance from home plate to the outfield wall. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WallInfo)
	int32 RightFieldWallHeight;
};