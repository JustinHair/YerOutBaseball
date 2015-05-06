// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "YOTeam.generated.h"

UCLASS()
class YEROUTBASEBALL_API AYOTeam : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AYOTeam();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

private:

	/**Variables for the team info*/
	// Team Name
};
