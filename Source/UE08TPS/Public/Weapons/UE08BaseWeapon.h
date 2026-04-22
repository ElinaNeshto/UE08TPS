// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UE08TPS.h"

#include "UE08BaseWeapon.generated.h"

UCLASS()
class UE08TPS_API AUE08BaseWeapon : public AActor
{
	GENERATED_BODY()
	
	//* METHODS *//

public:	
	
	AUE08BaseWeapon();

	void StartFire();

	void StopFire();

	UFUNCTION(BlueprintCallable)
	bool Reload();

	bool CanReload() const;

	void DecreaseAmmo();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsClipEmpty() const;

	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	FVector GetMuzzleWorldLocation() const;

	void MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd);

	bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

	void MakeShot();

	UFUNCTION(BlueprintImplementableEvent)
	void CreateProjectile(FVector ShotPoint, FVector ShotEndPoint, FRotator DeltaRotator);

	void SwitchIsReload();

	UFUNCTION(BlueprintCallable)
	void AddAmmo(int32 ClipsToAdd);

	UFUNCTION(BlueprintCallable, BlueprintPure) const
	FAmmoData GetCurrentAmmo() 
	{ 
		return CurrentAmmo; 
	};

protected:
	
	virtual void BeginPlay() override;

private:



	//* PROPERTIES *//

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool isNeedAmmo = false;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category ="UE08|Component")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UE08|Weapon")
	FName MuzzleSocketName = "b_gun_muzzleflash";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UE08|Weapon")
	float TraceMaxDistance = 1500.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UE08|Weapon")
	FAmmoData DefaultAmmo{30, 3};

	bool ReloadInProgress = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UE08|Weapon")
	UAnimationAsset* ReloadAnim;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UE08|Weapon")
	UAnimationAsset* FireAnim;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle ShotTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FTimerHandle ReloadTimerHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UE08|Weapon")
	float TimeBetweenShots = 0.3f;


	UPROPERTY()
	class UUE08BarrelComponent* BarrelComponent;

private:

	FAmmoData CurrentAmmo;
};
