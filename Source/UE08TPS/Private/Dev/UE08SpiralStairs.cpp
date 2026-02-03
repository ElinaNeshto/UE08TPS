// Fill out your copyright notice in the Description page of Project Settings.


#include "Dev/UE08SpiralStairs.h"


//
AUE08SpiralStairs::AUE08SpiralStairs()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* lRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = lRoot;

}

void AUE08SpiralStairs::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	if (!StepMesh || !CylinderMesh)
	{
		return;
	}

	DestroyStairComponents();

	
	FBoxSphereBounds lBounds;
	FVector lDimensions;
	int32 lTotalSteps = NumberOfTurns * StepsPerTurn;
	float lAngleStep = 360.0f / StepsPerTurn;

	for (int32 i = 0; i < lTotalSteps; i++)
	{
		FString lName = FString::Printf(TEXT("Step_%d"), i);
		UStaticMeshComponent* lStep = NewObject<UStaticMeshComponent>(this, *lName);

		lStep->SetStaticMesh(StepMesh);
		lStep->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

		lBounds = StepMesh->GetBounds();
		lDimensions = lBounds.GetBox().GetSize();

		FVector lSize = { 1, 1, Height / lDimensions.Z };
		lStep->SetRelativeScale3D(lSize);

		float lAngle = FMath::DegreesToRadians(i * lAngleStep);

		float lX = FMath::Cos(lAngle) * Radius;
		float lY = FMath::Sin(lAngle) * Radius;
		float lZ = i * Height;

		FVector lStepLocation = { lX, lY, lZ };

		lStep->SetRelativeLocation(lStepLocation);

		FRotator lStepRotation = { 0, i * lAngleStep, 0 };
		lStep->SetRelativeRotation(lStepRotation);
		lStep->RegisterComponent();

		StepComponent.Add(lStep);

	}

	UStaticMeshComponent* lCylinder = NewObject<UStaticMeshComponent>(this, "Cylinder");

	lCylinder->SetStaticMesh(CylinderMesh);
	lCylinder->AttachToComponent(this->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);

	lBounds = CylinderMesh->GetBounds();
	lDimensions = lBounds.GetBox().GetSize();

	FVector lScale = { Radius * 2.0f / lDimensions.X , Radius * 2.0f / lDimensions.Y, Height * lTotalSteps / lDimensions.Z };
	lCylinder->SetRelativeScale3D(lScale);
	lCylinder->RegisterComponent();

	
}


//
void AUE08SpiralStairs::BeginPlay()
{
	Super::BeginPlay();
}



//
void AUE08SpiralStairs::DestroyStairComponents()
{
	for (UStaticMeshComponent* lComp : StepComponent)
	{
		if (lComp)
		{
			lComp->DestroyComponent();

		}

	}

}