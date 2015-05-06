// Fill out your copyright notice in the Description page of Project Settings.

#include "YerOutBaseball.h"
#include "YOActorTests.h"
#include "AutomationTest.h"
#include "Actors/Public/YOStadium.h"

/*
*** Get/Set test verifies that the stadium class actors GetStadiumName and SetStadiumName are working properly. ***
* SetStadiumName -  Sets the stadiums private StadiumName FString variable to a new string.
* GetStadiumName -  returns the current private StadiumName FString variable.
*** Returns true if tests passes, otherwise false.
*/
IMPLEMENT_SIMPLE_AUTOMATION_TEST(FStadiumName, "YerOut.Actors.Stadium.Name - Set and Get", EAutomationTestFlags::ATF_FeatureMask)

bool FStadiumName::RunTest(const FString& Parameters)
{
	//***** SETUP *****/
	// Create the stadium actor and obtain the default stadium name so that we can use it for comparing later.
	AYOStadium* TestStadium = GWorld->SpawnActor<AYOStadium>();
	FString OriginalStadiumName = TestStadium->GetStadiumName();


	//***** TEST *****/
	// Set the stadium name to a new name that is different than the original.  Then use the get function to assign it to a new variable.
	TestStadium->SetStadiumName(TEXT("Test New Stadium Name"));
	FString NewStadiumName = TestStadium->GetStadiumName();


	//***** VERIFY *****/
	// Verify the original stadium name and the new set name are different by comparing the two.
	TestNotEqual<FString>(TEXT("Stadium Names are the same."), OriginalStadiumName, NewStadiumName);
	// Verify the new stadium name is the name that was given to it.
	TestEqual<FString>(TEXT("Stadium Name is not the set name."), NewStadiumName, TEXT("Test New Stadium Name"));


	//***** TEARDOWN *****/
	TestStadium->Destroy();

	return true;
}