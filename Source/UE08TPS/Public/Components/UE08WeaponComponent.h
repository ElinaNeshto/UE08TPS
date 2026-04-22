// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UE08WeaponComponent.generated.h"

class AUE08BaseWeapon;
class AUE08BaseCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE08TPS_API UUE08WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

	//** METHODS **//

public:	

	UUE08WeaponComponent();

	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();

	UFUNCTION(BlueprintCallable)
	bool Reload();

	UFUNCTION(BlueprintCallable)
	void NextWeapon();

	UFUNCTION(BlueprintCallable)
	void InitWeaponComponent();

private:

	UFUNCTION()
	void SpawnWeapon();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void EquipWeapon(int32 WeaponIndex);
	
	UFUNCTION()
	void AttachWeaponToSocket(AUE08BaseWeapon* WeaponToEquip, const FName& SocketName);

	//** PROPERTIES **//

public:	

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "UE08|Weapon")
	AUE08BaseWeapon* CurrentWeapon = nullptr;

protected:

	UPROPERTY(BlueprintReadOnly)
	TArray<AUE08BaseWeapon*> Weapons;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UE08|Weapons", meta= (AllowPrivateAccess = "true", DisplayName="Weapon classes"))
	TArray<TSubclassOf<AUE08BaseWeapon>> WeaponClasses;

	UPROPERTY(VisibleAnywhere, Category = "UE08|Weapons")
	int32 CurrentWeaponIndex = 0;

	UPROPERTY(EditDefaultsOnly)
	FName WeaponSocketName = "WeaponSocket";

	UPROPERTY(EditDefaultsOnly)
	FName WeaponArmorySocketName = "WeaponArmorySocket";

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	AUE08BaseCharacter* Owner;
};
