// Fill out your copyright notice in the Description page of Project Settings.

#include "YerOutBaseball.h"
#include "Actors/Public/YOTeam.h"


// Sets default values
AYOTeam::AYOTeam()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AYOTeam::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AYOTeam::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

