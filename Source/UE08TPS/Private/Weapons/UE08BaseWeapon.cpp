// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/UE08BaseWeapon.h"
#include "GameFramework/Character.h"
#include "Player/UE08BaseCharacter.h"
#include "Components/UE08BarrelComponent.h"

#include <Kismet/KismetSystemLibrary.h>

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

// 
AUE08BaseWeapon::AUE08BaseWeapon()
{
 
	PrimaryActorTick.bCanEverTick = false;
	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

	//BarrelComponent
	BarrelComponent = CreateDefaultSubobject<UUE08BarrelComponent>("Barrel Component");

}


// 
void AUE08BaseWeapon::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
	check(BarrelComponent);

	CurrentAmmo = DefaultAmmo;
}


//
void AUE08BaseWeapon::StartFire()
{
	if (!ReloadInProgress) 
	{
		GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AUE08BaseWeapon::MakeShot, TimeBetweenShots, true, 0.0f);
	}
	
}

//
void AUE08BaseWeapon::StopFire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHandle);
	
}


//
bool AUE08BaseWeapon::Reload()
{
	if (CurrentAmmo.Clips == 0)
	{
		UE_LOG(LogBaseWeapon, Warning, TEXT("No clips"));
		isNeedAmmo = true;
		return false;
	}

	if (CurrentAmmo.Bullets == DefaultAmmo.Bullets)
		return false;

	isNeedAmmo = false;
	ReloadInProgress = true;
	WeaponMesh->PlayAnimation(ReloadAnim, false);

	float lReloadAnimTime = ReloadAnim->GetPlayLength();

	GetWorldTimerManager().SetTimer(ReloadTimerHandle, this, &AUE08BaseWeapon::SwitchIsReload, 1.0f, false, lReloadAnimTime);

	CurrentAmmo.Clips--;
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;

	return true;
}

//
void AUE08BaseWeapon::DecreaseAmmo()
{

	CurrentAmmo.Bullets--;

	if (IsClipEmpty() )
	{
		UE_LOG(LogBaseWeapon, Warning, TEXT("Clip is empty"));

		StopFire();
		Reload();
	}
}

//
bool AUE08BaseWeapon::IsClipEmpty() const
{
	return CurrentAmmo.Bullets == 0;
}

//
bool AUE08BaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	const auto lBaseCharacter = Cast<AUE08BaseCharacter>(GetOwner());

	if (!lBaseCharacter)
		return false;

	TraceStart = GetMuzzleWorldLocation();

	FVector lAimPoint;
	FHitResult lHit;

	if (!lBaseCharacter->GetAimPoint(lHit, lAimPoint, TraceMaxDistance))
		return false;

	FVector lShootDirection = (lAimPoint - TraceStart).GetSafeNormal();

	if (lShootDirection.IsNearlyZero())
	{
		lShootDirection = lBaseCharacter->GetBaseAimRotation().Vector();
	}

	TraceEnd = TraceStart + lShootDirection * TraceMaxDistance;
	return true;


}

//
FVector AUE08BaseWeapon::GetMuzzleWorldLocation() const
{
	return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

//
void AUE08BaseWeapon::MakeHit(FHitResult& HitResult, FVector& TraceStart, FVector& TraceEnd)
{
	if (!GetWorld())
		return;

	FCollisionQueryParams lCollisionParams;
	lCollisionParams.AddIgnoredActor(GetOwner());

	if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, lCollisionParams))
	{
		TraceEnd = HitResult.ImpactPoint;
	}

	UKismetSystemLibrary::DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FLinearColor::Red, 1.0f, 1.0f);

}


//
bool AUE08BaseWeapon::GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto lBaseCharacter = Cast<AUE08BaseCharacter>(GetOwner());

	if (!lBaseCharacter)
		return false;

	if (lBaseCharacter->IsPlayerControlled())
	{
		const auto lController = lBaseCharacter->GetController<APlayerController>();
		if (!lController)
			return false;

		lController->GetPlayerViewPoint(ViewLocation, ViewRotation);

		ViewRotation = lController->GetControlRotation();
		ViewLocation = GetMuzzleWorldLocation();
		
	}
	else 
	{
		ViewLocation = GetMuzzleWorldLocation();
		ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
	}
	
	return true;
}

//
void AUE08BaseWeapon::MakeShot()
{
	if (IsClipEmpty())
	{
		StopFire();
		Reload();
		return;
	}

	//FVector lTraceStart, lTraceEnd;
	// GetTraceData(lTraceStart, lTraceEnd)
	// 
	//FQuat lDeltaRotation = FQuat::FindBetween(lTraceStar, lTraceEnd);
	//FRotator lDeltaRotator = lDeltaRotation.Rotator();
	
	//CreateProjectile(lTraceStar, lTraceEnd, lDeltaRotator);

	BarrelComponent->Shoot();

	//WeaponMesh->PlayAnimation(FireAnim, false);

	DecreaseAmmo();
}

//
void AUE08BaseWeapon::SwitchIsReload()
{
	ReloadInProgress = !ReloadInProgress;
}


//
void AUE08BaseWeapon::AddAmmo(int32 ClipsToAdd)
{
	CurrentAmmo.Clips += ClipsToAdd;
}



