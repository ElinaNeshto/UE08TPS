// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "UE08TPS.generated.h"

/** Main log category used across the project */
DECLARE_LOG_CATEGORY_EXTERN(LogUE08TPS, Log, All);

//** Health Delegates **//
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, Health, float, HealthDelta);


UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Physical    UMETA(DisplayName = "PhysicalDamage", ToolTip = "NormalDamage"),
	Fire        UMETA(DisplayName = "FireDamage", ToolTip = "BurnDamage"),
	Ice         UMETA(DisplayName = "IceDamage", ToolTip = "FrostDamage"),
	Explosion   UMETA(DisplayName = "ExplosionDamage", ToolTip = "BurnAndImpactDamage")
};

USTRUCT(BlueprintType) // , Blueprintable, Blueprintspawnable
struct FMyCharacterStats
{
	GENERATED_BODY()

public:
	FMyCharacterStats() {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Health = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Stamina = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CharacterLevel = 1;

};

