// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "YerOutBaseball.h"
#include "YOBallParks.generated.h"


/** Structure that defines the info for a teams ball park */
USTRUCT(BlueprintType)
struct FBallPark
{
	GENERATED_USTRUCT_BODY()

public:

	FBallPark()
		: ParkName(TEXT("Default Park"))
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Baseball)
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
