// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/UE08PlayerCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"


DEFINE_LOG_CATEGORY(LogPlayerCharacter)

AUE08PlayerCharacter::AUE08PlayerCharacter()
{

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}

//
void AUE08PlayerCharacter::HealthChanged(float Health, float DeltaHealth)
{
	Super::HealthChanged(Health, DeltaHealth);
	UE_LOG(LogPlayerCharacter, Error, TEXT("Player health was chaged"));

}



//
void AUE08PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogPlayerCharacter, Warning, TEXT("Player was created!"));
}

//
void AUE08PlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (Controller)
	{
		//Controller->ChangeState(FName Spectator);
	}
}

//
void AUE08PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);


	if (!EnhancedInputComponent) 
	{
		return;
	}

	// Jumping
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	// Moving
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUE08PlayerCharacter::Move);
	EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AUE08PlayerCharacter::Look);

	// Looking
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUE08PlayerCharacter::Look);
	
}

void AUE08PlayerCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AUE08PlayerCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

//
void AUE08PlayerCharacter::DoJumpStart()
{
	Jump();
}

//
void AUE08PlayerCharacter::DoJumpEnd()
{
	StopJumping();
}