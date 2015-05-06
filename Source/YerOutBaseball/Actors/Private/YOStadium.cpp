// Fill out your copyright notice in the Description page of Project Settings.

#include "YerOutBaseball.h"
#include "Actors/Public/YOStadium.h"

// define
#define MAX_ATTENDANCE				50000
#define CORNER_OUTFIELD_DISTANCE	320
#define ALLEYS_OUTFIELD_DISTANCE	360
#define CENTER_OUTFIELD_DISTANCE	405
#define WALL_HEIGHT					8

// Sets default values
AYOStadium::AYOStadium()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// The name of the stadium
	StadiumName = TEXT("YO Stadium");
	// The maximum attendance of fans at a single game for this stadium.
	StadiumMaxAttendance = MAX_ATTENDANCE;
	// Fence Distances.
	LeftFieldWallDistance = CORNER_OUTFIELD_DISTANCE;
	LeftCenterWallDistance = ALLEYS_OUTFIELD_DISTANCE;
	CenterWallDistance = CENTER_OUTFIELD_DISTANCE;
	RightCenterWallDistance = ALLEYS_OUTFIELD_DISTANCE;
	RightFieldWallDistance = CORNER_OUTFIELD_DISTANCE;
	// Wall heights
	LeftFieldWallHeight = WALL_HEIGHT;
	LeftCenterWallHeight = WALL_HEIGHT;
	CenterWallHeight = WALL_HEIGHT;
	RightCenterWallHeight = WALL_HEIGHT;
	RightFieldWallHeight = WALL_HEIGHT;
	// Turf
	OFTurf = EYOStadiumOFTurf::Grass;
	IFTurf = EYOStadiumIFTurf::Grass;
	FoulSize = EYOStadiumFoulTerritory::Medium;
}

// Called when the game starts or when spawned
void AYOStadium::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AYOStadium::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//**Functions that set the stadiums attributes.*/
void AYOStadium::SetStadiumName(const FString& InStadiumName)
{
	StadiumName = InStadiumName;
}

void AYOStadium::SetStadiumMaxAttendance(const int32& InNewMaxAttendance)
{
	StadiumMaxAttendance = InNewMaxAttendance;
}

//**Functions that 'Get' the stadiums attributes.*/
FString AYOStadium::GetStadiumName() const
{
	return StadiumName;
}

int32 AYOStadium::GetStadiumMaxAttendance() const
{
	return StadiumMaxAttendance;
}


