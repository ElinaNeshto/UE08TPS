// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/UE08TriggerPlatform.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/UE08BaseCharacter.h"


//
AUE08TriggerPlatform::AUE08TriggerPlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	//SetNetUpdateFrequency(2.0f);

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(PlatformMesh);

}


//

void AUE08TriggerPlatform::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	FDoRepLifetimeParams RepParams;
	RepParams.RepNotifyCondition = REPNOTIFY_Always;

	//DOREPLIFETIME_WITH_PARAMS( AUE08TriggerPlatform, bIsActivated, RepParams );
	//DOREPLIFETIME(AUE08TriggerPlatform, bIsActivated);

}


//
void AUE08TriggerPlatform::BeginPlay()
{
	Super::BeginPlay();

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AUE08TriggerPlatform::OnTriggerOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AUE08TriggerPlatform::OnTriggerOverlapEnd);

	//this->OnTriggerActivated.AddDynamic(this, &AUE08TriggerPlatform::OnPlatformTriggerActivated);

}


//
void AUE08TriggerPlatform::OnPlatformTriggerActivated(bool bIsActivated_In)
{
	bIsActivated_In = bIsActivated;

}

//

void AUE08TriggerPlatform::HandleProgress(float Value)
{
	FVector NewLocation = FMath::Lerp(StartLocation, StartLocation + TargetLocation, Value);
	SetActorLocation(NewLocation);
}



//
void AUE08TriggerPlatform::Server_SetIsActivated_Implementation(bool bIsActivated_In)
{
	SetIsActivated(bIsActivated_In);

}



//
void AUE08TriggerPlatform::Multicast_SetIsActivated_Implementation(bool bIsActivated_In)
{
	bIsActivated = bIsActivated_In;

	if (bIsActivated_In)
	{
		// TODO;

		StartLocation = GetActorLocation();


		if (FloatCurve)
		{
			FOnTimelineFloat ProgressUpdate;
			ProgressUpdate.BindDynamic(this, &AUE08TriggerPlatform::HandleProgress);
			MyTimeline.AddInterpFloat(FloatCurve, ProgressUpdate);
			MyTimeline.PlayFromStart();


		}


	}

	if (!HasAuthority())
	{
		if (OnTriggerActivated.IsBound())
		{
				OnTriggerActivated.Broadcast(bIsActivated);

		}
	}

}


//
void AUE08TriggerPlatform::Client_SetIsActivated_Implementation(bool bIsActivated_In)
{
	SetIsActivated(bIsActivated);
}



//
void AUE08TriggerPlatform::OnRep_IsActivated(bool bIsActivated_Old)
{
	SetIsActivated(bIsActivated);

}



//
void AUE08TriggerPlatform::SetIsActivated(bool bIsActivated_In)
{
	bIsActivated = bIsActivated_In;

	if (OnTriggerActivated.IsBound())
	{
		OnTriggerActivated.Broadcast(bIsActivated);

	}

}



//
void AUE08TriggerPlatform::OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{


	//APawn* OtherPawn = Cast<APawn>( OtherActor );

	AUE08BaseCharacter* OtherPawn = Cast<AUE08BaseCharacter>(OtherActor);

	if (!IsValid(OtherPawn))
		return;

	if (GetLocalRole() == ROLE_Authority) // OtherPawn->IsLocallyControlled() || GetLocalRole() == ROLE_Authority
	{
		OverlappedPawns.AddUnique(OtherPawn);

		if (!bIsActivated && OverlappedPawns.Num() > 0)
		{
			//bIsActivated = true;
			//SetIsActivated(true);
			Multicast_SetIsActivated( true );
			//Server_SetIsActivated( true );
			//OtherPawn->Server_PlatformActivate( this, true );
			//OtherPawn->Client_PlatformActivate(this, true);

		}

	}

}




//
void AUE08TriggerPlatform::OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//APawn* OtherPawn = Cast<APawn>( OtherActor );


	AUE08BaseCharacter* OtherPawn = Cast<AUE08BaseCharacter>(OtherActor);

	if (!IsValid(OtherPawn))
		return;

	OverlappedPawns.RemoveSingleSwap(OtherPawn);


	if (GetLocalRole() == ROLE_Authority) // OtherPawn->IsLocallyControlled() || GetLocalRole() == ROLE_Authority
	{
		if (bIsActivated && OverlappedPawns.Num() == 0)
		{
			//bIsActivated = false;
			//SetIsActivated(false);
			Multicast_SetIsActivated( false );
			//Server_SetIsActivated( false );
			//OtherPawn->Server_PlatformActivate( this, false );
			//OtherPawn->Client_PlatformActivate(this, false);

		}

	}

}

void AUE08TriggerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MyTimeline.TickTimeline(DeltaTime); // Обновление таймлайна

}


