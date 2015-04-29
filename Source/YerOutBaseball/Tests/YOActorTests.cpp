// Fill out your copyright notice in the Description page of Project Settings.

#include "YerOutBaseball.h"
#include "YOActorTests.h"
#include "AutomationTest.h"
#include "YOStadium.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FStadiumName, "YerOut.Actors.Stadium.Name - Set and Get", EAutomationTestFlags::ATF_Game)

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
	TestFalse(TEXT("Stadium Names are the same."), OriginalStadiumName == NewStadiumName);
	// Verify the new name is the name that was given to it.
	TestTrue(TEXT("Stadium Name is not the set name."), NewStadiumName == TEXT("Test New Stadium Name"));

	//***** TEARDOWN *****/
	// Destroy the TestStadium Actor.
	return TestStadium->Destroy();
}