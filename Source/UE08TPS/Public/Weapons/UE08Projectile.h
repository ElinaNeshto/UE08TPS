// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE08Projectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;


UCLASS()
class UE08TPS_API AUE08Projectile : public AActor
{
	GENERATED_BODY()
	
public:	

	AUE08Projectile();


protected:

	virtual void BeginPlay() override;

private:

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent,
						AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
						const FHitResult& Hit);

	AController* GetController() const;

	//* PROPERTIES *//

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UProjectileMovementComponent* MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Damage = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float LifeSeconds = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool bDoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float DamageRadius = 0.0f;

protected:


public:

};
