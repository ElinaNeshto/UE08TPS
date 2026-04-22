// Fill out your copyright notice in the Description page of Project Settings.


#include "Dev/UE08UnitTest.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Player/UE08PlayerCharacter.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST( FMyTestClass, "UE08.CustomTests.UnitTest",
	EAutomationTestFlags::EditorContext |
	EAutomationTestFlags::HighPriority  |
	EAutomationTestFlags::ProductFilter)


bool FMyTestClass::RunTest(const FString& Parameters)
{
	AUE08PlayerCharacter* PlayerCharacter = NewObject< AUE08PlayerCharacter>();
	bool result = TestTrue("Random bool", PlayerCharacter->RandomizedValue());
	return result;
}

UE08UnitTest::UE08UnitTest()
{
}

UE08UnitTest::~UE08UnitTest()
{
}
