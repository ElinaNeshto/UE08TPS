// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE08TPS.h"

#include "UE08Weapon.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUE08Weapon, All, All)

DECLARE_DELEGATE_OneParam(FMyDelegate, bool);

UCLASS()
class UE08TPS_API AUE08Weapon : public AActor
{
	GENERATED_BODY()
	
	/*PROPERTIES*/

public:	

	AUE08Weapon();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxGrabDistance = 500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UE08|Weapon", meta = (ClampMin = 0, ClampMax = 50))
	int32 Capacity = 20;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "UE08|Weapon", meta = (ClampMin = 0, ClampMax = 100))
	int32 Ammo = 50;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "UE08|Weapon")
	bool isEquiped = false;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "UE08|Weapon", meta = (ClampMin = 10.0f, ClampMax = 50.0f))
	float Damage = 10.0f;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 100, Category = "UE08|DEBUG_PROPERTIES"))
	float TimeDuration = 5.0f;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 100, Category = "UE08|DEBUG_PROPERTIES"))
	FColor DebugColor = { 255, 0, 0, 255 };

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 12, Category = "UE08|DEBUG_PROPERTIES"))
	FString DebugText = TEXT("Fire Weapon");

	FMyDelegate OnSomethingHappened;

	/*METHODS*/

public:

	UFUNCTION(BlueprintCallable, Category = "UE08|Weapon|Actions")
	void FireWeapon();

	UFUNCTION(BlueprintPure, Category = "UE08|Calculations")
	float SumOfTwo(float A, float B) const;

	UFUNCTION(BlueprintImplementableEvent, Category = "UE08|Initialization")
	float InitMyWeapon();

	UFUNCTION(BlueprintNativeEvent, Category = "UE08|Initialization")
	void InitActor();
	void InitActor_Implementation();

	UFUNCTION(BlueprintPure)
	FVector GetMaxGrabLocation() const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void NotifyActor(AActor* Actor);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)

	bool TraceResponce(AActor* HitActor, UPrimitiveComponent* HitComponent);//без реализации
	bool TraceResponce_Implementation(AActor* HitActor, UPrimitiveComponent* HitComponent);

	UFUNCTION()
	void DelegateTest(bool bIsSuccess);

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	bool ThrowLineTrace(FHitResult& HitResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EDamageType DamageType;

};
