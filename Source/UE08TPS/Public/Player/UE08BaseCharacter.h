#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UE08BaseCharacter.generated.h"

UCLASS()
class UE08TPS_API AUE08BaseCharacter : public ACharacter
{
	GENERATED_BODY()

	//** METHODS **//

public:

	AUE08BaseCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void HealthChanged(float Health, float HealthDelta);

	virtual void PostInitializeComponents() override;

	UFUNCTION(Server, Reliable)
	void Server_PlatformActivate(class AUE08TriggerPlatform* TriggerPlatform, bool bIsActivate_In);

	UFUNCTION(Client, Reliable)
	void Client_PlatformActivate(class AUE08TriggerPlatform* TriggerPlatform, bool bIsActivate_In);

	UFUNCTION(BlueprintCallable)
	bool GetAimPoint(FHitResult& HitResult, FVector& OutPoint, float MaxDistance) const;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnDeath();

private:




	//** PROPERTIES **//

public:


protected:

	UPROPERTY(EditDefaultsOnly)
	class UUE08HealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly)
	class UUE08WeaponComponent* WeaponComponent;

private:


};
