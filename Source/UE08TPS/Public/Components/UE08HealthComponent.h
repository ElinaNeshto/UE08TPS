// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UE08TPS.h"

#include "UE08HealthComponent.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUE08HealthComponent, All, All)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE08TPS_API UUE08HealthComponent : public UActorComponent
{
	GENERATED_BODY()

	//** METHODS **//

public:	
	UUE08HealthComponent();

	UFUNCTION()
	void InitHealthComponent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	FORCEINLINE float GetHealth() { return Health; }


	UFUNCTION()
	void GetDamage(AActor* DamageActor, 
				   float Damage, 
				   const UDamageType* DamageType,
				   AController* InstigatedBy, 
				   AActor* DamageCauser );


	UFUNCTION()
	void SetHealth(float newHealth);

	UFUNCTION()
	bool IsDead() const
	{
		return FMath::IsNearlyZero(Health);
	};

	//** PROPERTIES **//

public:

	UPROPERTY()
	float MaxHealth = 100.0f;

	FOnDeathSignature OnDeath;

	FOnHealthChangedSignature OnHealthChanged;

protected:


private:

	UPROPERTY()
	float Health = 0.0f;
		
};
