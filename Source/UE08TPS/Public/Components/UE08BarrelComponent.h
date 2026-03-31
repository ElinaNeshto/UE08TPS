// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UE08BarrelComponent.generated.h"

class AUE08BaseWeapon;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE08TPS_API UUE08BarrelComponent : public UActorComponent
{
	GENERATED_BODY()

	//** METHODS **//

public:	
	UUE08BarrelComponent();

	UFUNCTION(BlueprintCallable)
	void Shoot();



private:

protected:

	virtual void BeginPlay() override;

	//** PROPERTIES **//

public:	


private:

protected:
};