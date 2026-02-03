// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "UE08SpiralStairs.generated.h"


UCLASS()
class UE08TPS_API AUE08SpiralStairs : public AActor
{
	GENERATED_BODY()

	//** PROPERTIES **//

public:

	UPROPERTY(EditAnywhere, Category = "Stair Settings")
	UStaticMesh* StepMesh;

	UPROPERTY(EditAnywhere, Category = "Stair Settings")
	UStaticMesh* CylinderMesh;

	UPROPERTY(EditAnywhere, Category = "Stair Settings", meta = (ClampMin = "1.0"))
	float Height = 20.0f; //высота ступеньки

	UPROPERTY(EditAnywhere, Category = "Stair Settings", meta = (ClampMin = "-2000.0", ClampMax = "2000.0"))
	float Radius = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Stair Settings", meta = (ClampMin = "3"))
	int32 StepsPerTurn = 15;

	UPROPERTY(EditAnywhere, Category = "Stair Settings", meta = (ClampMin = "1"))
	int32 NumberOfTurns = 3;

protected:


private:

	TArray<UStaticMeshComponent*> StepComponent;


	//** METHODS **//

public:

	AUE08SpiralStairs();

	virtual void OnConstruction(const FTransform& Transform) override;


protected:

	virtual void BeginPlay() override;

	void DestroyStairComponents();


private:

	




};
