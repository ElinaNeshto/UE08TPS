// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimeLineComponent.h"
#include "UE08TriggerPlatform.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTriggerBoxActivatedSignature, bool, bIsActivated);


UCLASS()
class UE08TPS_API AUE08TriggerPlatform : public AActor
{
	GENERATED_BODY()


	/** METHODS **/

public:

	AUE08TriggerPlatform();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void SetIsActivated(bool bIsActivated_In);

	UFUNCTION()
	void OnRep_IsActivated(bool bIsActivated_Old);


	UFUNCTION(NetMulticast, Reliable) // Server -> All clients
	void Multicast_SetIsActivated(bool bIsActivated_In);

	UFUNCTION(Server, Reliable) // Server - AutonomousProxy // Client (Char) -> Server
	void Server_SetIsActivated(bool bIsActivated_In);

	UFUNCTION(Client, Reliable) // Server -> One client
	void Client_SetIsActivated(bool bIsActivated_In);

	virtual void Tick(float DeltaTime) override;



protected:

	virtual void BeginPlay() override;


private:

	UFUNCTION()
	void OnTriggerOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnPlatformTriggerActivated(bool bIsActivated_In);

	UFUNCTION()
	void HandleProgress(float Value);




	/** PROPERTIES **/

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	class UBoxComponent* TriggerBox;

	UPROPERTY(BlueprintAssignable)
	FOnTriggerBoxActivatedSignature OnTriggerActivated;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* FloatCurve;

	UPROPERTY(EditDefaultsOnly)
	FVector TargetLocation;


	

protected:

	//UPROPERTY(ReplicatedUsing = OnRep_IsActivated)
	bool bIsActivated = false;




private:

	TArray<APawn*> OverlappedPawns;

	FTimeline MyTimeline;

	FVector StartLocation;

};

