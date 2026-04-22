#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "UE08TPS.h"
#include "UE08BaseCharacter.generated.h"


class UUE08WeaponComponent;
class UAnimMontage;

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

	UFUNCTION(BlueprintCallable, BlueprintPure) const
	UUE08WeaponComponent* GetWeaponComponent()
	{
		return WeaponComponent;
	}

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnDeath();

private:




	//** PROPERTIES **//

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* ReloadAnimRifle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UAnimMontage* ReloadAnimPistol;

protected:

	UPROPERTY(EditDefaultsOnly)
	class UUE08HealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly)
	UUE08WeaponComponent* WeaponComponent;

	UPROPERTY(BlueprintReadWrite)
	EEquippedWeaponType EquippedWeaponType;

private:


};
