// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UE08PlayerController.generated.h"

class UInputMappingContext;

/**
 * 
 */
UCLASS()
class UE08TPS_API AUE08PlayerController : public APlayerController
{
	GENERATED_BODY()

	//** METHODS **//

protected:

	/** Gameplay initialization */
	virtual void BeginPlay() override;

	/** Input mapping context setup */
	virtual void SetupInputComponent() override;
	




	//** PROPERTIES **//

protected:

	/** Input Mapping Contexts */
	UPROPERTY(EditAnywhere, Category = "UE08|Input|Input Mappings")
	TArray<class UInputMappingContext*> DefaultMappingContexts;
};
