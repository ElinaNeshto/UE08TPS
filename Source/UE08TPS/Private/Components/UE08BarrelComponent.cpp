// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UE08BarrelComponent.h"
#include "Weapons/UE08BaseWeapon.h"
#include "Weapons/UE08Projectile.h"
#include <Kismet/KismetSystemLibrary.h>


DEFINE_LOG_CATEGORY_STATIC(LogBarrelComponent, All, All)

// 
UUE08BarrelComponent::UUE08BarrelComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


// 
void UUE08BarrelComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


//
void UUE08BarrelComponent::Shoot()
{

	class AActor* lActorOwner = GetOwner();
	
	if (!lActorOwner)
		return;

	class AUE08BaseWeapon* lWeaponOwner = Cast<AUE08BaseWeapon>(GetOwner());

	FHitResult lTempHitResult;
	FVector lTempStart = FVector::ZeroVector;
	FVector lTempEnd = FVector::ZeroVector;


	if (lWeaponOwner)
	{
		lWeaponOwner->GetTraceData(lTempStart, lTempEnd);
		lWeaponOwner->MakeHit(lTempHitResult, lTempStart, lTempEnd);
	}
	else
	{
		FCollisionQueryParams lCollisionParams;
		lCollisionParams.AddIgnoredActor(GetOwner());
		lTempStart = GetOwner()->GetActorLocation();
		lTempEnd = lTempStart + GetOwner()->GetActorForwardVector() * 1500.0f;

		if (GetWorld()->LineTraceSingleByChannel(lTempHitResult, lTempStart, lTempEnd, ECollisionChannel::ECC_Visibility, lCollisionParams))
		{
			lTempEnd = lTempHitResult.ImpactPoint;
			//UE_LOG(LogBarrelComponent, Warning, TEXT("lActorOwner"));
		}


		UKismetSystemLibrary::DrawDebugLine(GetWorld(), lTempStart, lTempEnd, FLinearColor::Red, 1.0f, 1.0f);

	}

	

}

