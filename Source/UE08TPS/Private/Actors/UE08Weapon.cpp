// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/UE08Weapon.h"

#include "Engine/Engine.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

DEFINE_LOG_CATEGORY(LogUE08Weapon)

// 
AUE08Weapon::AUE08Weapon()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogUE08Weapon, Error, TEXT("Test Actor start his Constructor"));

	switch (DamageType)
	{
		case EDamageType::Physical:
			UE_LOG(LogUE08Weapon, Warning, TEXT("Physical Damage"));
			break;
		case EDamageType::Fire:
			UE_LOG(LogUE08Weapon, Warning, TEXT("Fire Damage"));
			break;
		case EDamageType::Ice:
			UE_LOG(LogUE08Weapon, Warning, TEXT("Ice Damage"));
			break;
		case EDamageType::Explosion:
			UE_LOG(LogUE08Weapon, Warning, TEXT("Explosion Damage"));
			break;
	}
}


//
void AUE08Weapon::FireWeapon()
{
	

	GEngine->AddOnScreenDebugMessage(-1, TimeDuration, DebugColor, DebugText);
}

float AUE08Weapon::SumOfTwo(float A, float B) const
{
	return A+B;
}


//
void AUE08Weapon::InitActor_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, TimeDuration, DebugColor, TEXT("InitActor from CPP"));
}

FVector AUE08Weapon::GetMaxGrabLocation() const
{
	
	return GetActorLocation() + GetActorRotation().Vector() * MaxGrabDistance;
}





bool AUE08Weapon::TraceResponce_Implementation(AActor* HitActor, UPrimitiveComponent* HitComponent)
{
	UE_LOG(LogUE08Weapon, Error, TEXT("Hit to %s in %s"), *HitActor->GetName(), *HitComponent->GetName());

	FString ActorName(*HitActor->GetName());
	FString ComponentName(*HitComponent->GetName());
	int32 WeaponDamage = 666;

	UE_LOGFMT(LogUE08Weapon, Error, "Hit to {0} in {1} with {2} dsmsge", ActorName, ComponentName, WeaponDamage);
	return false;
}

void AUE08Weapon::DelegateTest(bool bIsSuccess)
{
	if (bIsSuccess) 
	{
		GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Red, TEXT("Hello, World!"));
		UE_LOG(LogUE08Weapon, Warning, TEXT("Delegate call DelegateTest function"));
	}
	
	
}


// 
void AUE08Weapon::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogUE08Weapon, Warning, TEXT("Test Actor start his BeginPlay"));

	OnSomethingHappened.BindUObject(this, &AUE08Weapon::DelegateTest);


}

void AUE08Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AUE08Weapon::ThrowLineTrace(FHitResult& HitResult)
{
	

	if (GetWorld())
	{
		
		FCollisionQueryParams QueryParams;
		QueryParams.bTraceComplex = true;

		bool bIsHitSuccess = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			GetActorLocation(),
			GetMaxGrabLocation(),
			ECollisionChannel::ECC_Pawn,
			QueryParams);
			
		
		OnSomethingHappened.ExecuteIfBound(bIsHitSuccess);
		return bIsHitSuccess;
	}

	return false;
	

	/*bool HitSuccess = UKismetSystemLibrary::LineTraceSingle(
		GetWorld(),
		GetActorLocation(),
		GetMaxGrabLocation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		{},
		EDrawDebugTrace::ForDuration,
		HitResult,
		true,
		FLinearColor::Red,
		FLinearColor::Green,
		15.0f);

	return HitSuccess;*/
}


