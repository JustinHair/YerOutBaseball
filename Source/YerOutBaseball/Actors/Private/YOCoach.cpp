// Fill out your copyright notice in the Description page of Project Settings.

#include "YerOutBaseball.h"
#include "Actors/Public/YOCoach.h"

YOCoach::YOCoach()
{
	Name = TEXT("YO Coach");
	bIsIBBOpposingBatter = false;
	bIsStealing = false;
}

YOCoach::~YOCoach()
{
}
