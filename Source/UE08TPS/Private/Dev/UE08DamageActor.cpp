// Fill out your copyright notice in the Description page of Project Settings.


#include "Dev/UE08DamageActor.h"
#include "Kismet/GameplayStatics.h"

AUE08DamageActor::AUE08DamageActor()
{
	PrimaryActorTick.bCanEverTick = true;

}


// 
void AUE08DamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// 
void AUE08DamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, Segments, FColor::Red);
	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, DamageType, {}, this, nullptr, bDoFullDamage, ECollisionChannel::ECC_Visibility);
}

