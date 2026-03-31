// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/UE08BaseCharacter.h"
#include "UE08AICharacter.generated.h"

/**
 * 
 */

class UBehaviorTree;

UCLASS()
class UE08TPS_API AUE08AICharacter : public AUE08BaseCharacter
{
	GENERATED_BODY()
	
public:
	AUE08AICharacter();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBehaviorTree* BehaviorTreeAsset;

protected:

	virtual void BeginPlay() override;
};
