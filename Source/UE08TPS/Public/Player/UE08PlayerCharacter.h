// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/UE08BaseCharacter.h"
#include "InputActionValue.h"
#include "InputAction.h"
#include "UE08PlayerCharacter.generated.h"


DECLARE_LOG_CATEGORY_EXTERN(LogPlayerCharacter, Log, All);

/**
 * 
 */
UCLASS()
class UE08TPS_API AUE08PlayerCharacter : public AUE08BaseCharacter
{
	GENERATED_BODY()


	//** METHODS **//
	
public:

	AUE08PlayerCharacter();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category = "UE08|Input")
	virtual void DoJumpStart();

	/** Handles jump pressed inputs from either controls or UI interfaces */
	UFUNCTION(BlueprintCallable, Category = "UE08|Input")
	virtual void DoJumpEnd();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	virtual void HealthChanged(float Health, float DeltaHealth) override;


protected:

	virtual void BeginPlay() override;

	virtual void OnDeath() override;

	/** Initialize input action bindings */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

private:




	//** PROPERTIES **//

public:

protected:


private:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UE08|Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UE08|Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, Category = "UE08|Input")
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, Category = "UE08|Input")
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, Category = "UE08|Input")
	UInputAction* LookAction;

	/** Mouse Look Input Action */
	UPROPERTY(EditAnywhere, Category = "UE08|Input")
	UInputAction* MouseLookAction;

};
