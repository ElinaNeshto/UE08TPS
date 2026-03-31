// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UE08WeaponComponent.h"
#include "Weapons/UE08BaseWeapon.h"
#include "Player/UE08BaseCharacter.h"

#include <Kismet/GameplayStatics.h>


DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

// 
UUE08WeaponComponent::UUE08WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// 
void UUE08WeaponComponent::BeginPlay()
{
	Super::BeginPlay();
}

//
void UUE08WeaponComponent::InitWeaponComponent()
{
	Owner = Cast<AUE08BaseCharacter>(GetOwner());

	if (!Owner)
	{
		UE_LOG(LogWeaponComponent, Warning, TEXT("InitWeaponComponent: No valid Owner"));
		return;
	}

	for (AUE08BaseWeapon* Weapon : Weapons)
	{
		if (IsValid(Weapon))
			Weapon->Destroy();
	}

	Weapons.Empty();
	CurrentWeapon = nullptr;

	SpawnWeapon();
	if (Weapons.IsEmpty())
	{
		UE_LOG(LogWeaponComponent, Warning, TEXT("InitWeaponComponent: No weapons spawned. Check WeaponClasses on the character's Weapon Component (add at least one weapon)"));
		return;
	}

	EquipWeapon(CurrentWeaponIndex);

}

//
void UUE08WeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	if (Weapons.IsEmpty() || !Weapons.IsValidIndex(WeaponIndex))
		return;

	AUE08BaseWeapon* lNewWeapon = Weapons[WeaponIndex];
	if (!IsValid(lNewWeapon))
		return;

	if (IsValid(CurrentWeapon) && CurrentWeapon != lNewWeapon)
	{
		CurrentWeapon->StopFire();
		AttachWeaponToSocket(CurrentWeapon, WeaponArmorySocketName);
	}

	CurrentWeapon = lNewWeapon;
	AttachWeaponToSocket(CurrentWeapon, WeaponSocketName);
	CurrentWeaponIndex = WeaponIndex;
}

//
void UUE08WeaponComponent::AttachWeaponToSocket(AUE08BaseWeapon* WeaponToEquip, const FName& SocketName)
{
	auto lCharMesh = Owner->GetMesh();
	if (!lCharMesh || !WeaponToEquip)
		return;

	FAttachmentTransformRules lAttachmentRules(EAttachmentRule::SnapToTarget, true);
	WeaponToEquip->AttachToComponent(lCharMesh, lAttachmentRules, SocketName);
}

//
void UUE08WeaponComponent::StartFire()
{
	//if (!IsValid(CurrentWeapon) && !Weapons.IsEmpty())
	//	EquipWeapon(FMath::Clamp(CurrentWeaponIndex, 0, Weapons.Num() - 1));

	if (!IsValid(CurrentWeapon))
		return;

	CurrentWeapon->StartFire();
}

//
void UUE08WeaponComponent::StopFire()
{
	if (!IsValid(CurrentWeapon))
		return;

	CurrentWeapon->StopFire();
}

//
void UUE08WeaponComponent::Reload()
{
	if (!IsValid(CurrentWeapon))
		return;

	CurrentWeapon->Reload();
}

//
void UUE08WeaponComponent::NextWeapon()
{
	if (Weapons.IsEmpty())
		return;

	CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	EquipWeapon(CurrentWeaponIndex);
}

//
void UUE08WeaponComponent::SpawnWeapon()
{
	if (!GetWorld())
		return;

	for (TSubclassOf<AUE08BaseWeapon> WeaponClass : WeaponClasses)
	{
		if (!WeaponClass)
			continue;

		AUE08BaseWeapon* SpawnedWeapon = GetWorld()->SpawnActor<AUE08BaseWeapon>(WeaponClass);

		if (!SpawnedWeapon)
			continue;

		SpawnedWeapon->SetOwner(Owner);
		AttachWeaponToSocket(SpawnedWeapon, WeaponArmorySocketName);
		Weapons.Add(SpawnedWeapon);

	}

}




