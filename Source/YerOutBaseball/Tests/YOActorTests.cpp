// Fill out your copyright notice in the Description page of Project Settings.

#include "YerOutBaseball.h"
#include "YOActorTests.h"
#include "AutomationTest.h"
#include "YOStadium.h"

/*
*** Get/Set test verifies that the stadium class actors GetStadiumName and SetStadiumName are working properly. ***
* SetStadiumName -  Sets the stadiums private StadiumName FString variable to a new string.
* GetStadiumName -  returns the current private StadiumName FString variable.
* Returns true if tests passes, otherwise false.
*/
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FStadiumName, "YerOut.Actors.Stadium.Name - Set and Get", EAutomationTestFlags::ATF_FeatureMask)

bool FStadiumName::RunTest(const FString& Parameters)
{
	//***** SETUP *****/
	// Create Stadium Actor
	AYOStadium* TestStadium = GWorld->SpawnActor<AYOStadium>();
	// Get the Stadium Original Name
	FString OriginalStadiumName = TestStadium->GetStadiumName();


	//***** TEST *****/
	// Set the stadium name to a different name.
	TestStadium->SetStadiumName(TEXT("Test New Stadium Name"));
	// Get the stadiums new name.
	FString NewStadiumName = TestStadium->GetStadiumName();


	//***** VERIFY *****/
	// Verify the original name and the set name are different.
	TestNotEqual<FString>(TEXT("Stadium Names are the same."), OriginalStadiumName, NewStadiumName);
	// Verify the new name is the name that was given to it.
	TestEqual<FString>(TEXT("Stadium Name is not the set name."), NewStadiumName, TEXT("Test New Stadium Name"));


	//***** TEARDOWN *****/
	// Destroy the TestStadium Actor.
	TestStadium->Destroy();

	return true;
}