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

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnDeath();

private:




	//** PROPERTIES **//

public:


protected:

	class UUE08HealthComponent* HealthComponent;

private:


};
