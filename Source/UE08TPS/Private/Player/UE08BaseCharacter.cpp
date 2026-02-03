#include "Player/UE08BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/UE08HealthComponent.h"

// 
AUE08BaseCharacter::AUE08BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	//Health Component
	HealthComponent = CreateDefaultSubobject<UUE08HealthComponent>("Health Component");

}

// 
void AUE08BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);

	HealthComponent->OnDeath.AddDynamic(this, &AUE08BaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddDynamic(this, &AUE08BaseCharacter::HealthChanged);



}

//
void AUE08BaseCharacter::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);

}

//
void AUE08BaseCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	HealthComponent->InitHealthComponent();
}


// 
void AUE08BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUE08BaseCharacter::HealthChanged(float Health, float HealthDelta)
{

}
