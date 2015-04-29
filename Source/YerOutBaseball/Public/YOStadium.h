// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "YOStadium.generated.h"


UENUM(BlueprintType)
namespace EYOStadiumOFTurf
{
	enum Type
	{
		Dirt,				// The entire outfield is dirt. More likely to cause errors.
		Grass,				// The entire outfield is grass. Ground balls don't roll as far.
		Artifical,			// The entire outfield is artifical turf.  Ground balls roll farther.  More likely to cause injuries.
		Unknown,			// Who knows what happened...
	};
}

UENUM(BlueprintType)
namespace EYOStadiumIFTurf
{
	enum Type
	{
		Dirt,				// The entire infield is dirt. More likely to cause errors.
		Grass,				// The entire infield is grass. Ground balls don't roll as far. 
		Artifical,			// The entire infield is artifical turf.  Ground balls roll farther.  More likely to cause injuries.
		Unknown,			// Who knows what happened...
	};
}

UENUM(BlueprintType)
namespace EYOStadiumFoulTerritory
{
	enum Type
	{
		Small,				// Small Territory, favors the batter.
		Medium,				// Medium terriroty - neutral
		Large,				// Large foul territory - favors the pitcher.
		Unknown,			// Who knows what happened...
	};
}

UCLASS()
class YEROUTBASEBALL_API AYOStadium : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYOStadium();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	//**Functions that 'Set' the stadiums attributes.*/
	UFUNCTION(BlueprintCallable, Category = "Baseball.Stadium")
	void SetStadiumName(const FString& InStadiumName);
	UFUNCTION(BlueprintCallable, Category = "Baseball.Stadium")
	void SetStadiumMaxAttendance(const int32& InNewMaxAttendance);

	//**Functions that 'Get' the stadiums attributes.*/
	UFUNCTION(BlueprintCallable, Category = "Baseball.Stadium")
	FString GetStadiumName() const;
	UFUNCTION(BlueprintCallable, Category = "Baseball.Stadium")
	int32 GetStadiumMaxAttendance() const;


private:
	/**Variables for the stadiums*/

	//The name of the stadium
	FString StadiumName;
	//The maximum attendance of fans at a single game for this stadium.
	int32 StadiumMaxAttendance;
	//Fence Distances.
	int32 LeftFieldWallDistance;
	int32 LeftCenterWallDistance;
	int32 CenterWallDistance;
	int32 RightCenterWallDistance;
	int32 RightFieldWallDistance;
	//Wall heights
	int32 LeftFieldWallHeight;
	int32 LeftCenterWallHeight;
	int32 CenterWallHeight;
	int32 RightCenterWallHeight;
	int32 RightFieldWallHeight;
	//Outfield Turf
	EYOStadiumOFTurf::Type OFTurf;
	//Infield Turf
	EYOStadiumIFTurf::Type IFTurf;
	//The size of the on field foul ball territory.
	EYOStadiumFoulTerritory::Type FoulSize;
	
};
