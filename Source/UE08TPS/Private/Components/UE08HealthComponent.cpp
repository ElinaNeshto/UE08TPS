#include "Components/UE08HealthComponent.h"

DEFINE_LOG_CATEGORY(LogUE08HealthComponent)

// 
UUE08HealthComponent::UUE08HealthComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}


// 
void UUE08HealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
	UE_LOG(LogUE08HealthComponent, Warning, TEXT("Health Component was created!"));
}

//
void UUE08HealthComponent::InitHealthComponent()
{
	AActor* Owner = GetOwner();

	if (Owner)
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &UUE08HealthComponent::GetDamage);
		SetHealth(99.0f);
	}
}

//
void UUE08HealthComponent::GetDamage(AActor* DamageActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser )
{

	UE_LOG(LogUE08HealthComponent, Warning, TEXT("Hey"));

	if (Damage <= 0.0f || IsDead())
	{
		return;
	}

	float newHealth = Health - Damage;
	UE_LOG(LogUE08HealthComponent, Warning, TEXT("Character get %f damage. Current health is: %f"), Damage, newHealth);

	SetHealth(newHealth);

	if (IsDead())
	{
		OnDeath.Broadcast();
		UE_LOG(LogUE08HealthComponent, Warning, TEXT("Player is dead!"));
	}
}


//
void UUE08HealthComponent::SetHealth(float newHealth)
{
	float UpdatedHealth = FMath::Clamp(newHealth, 0.0f, MaxHealth);
	float HealthDelta = UpdatedHealth - Health;

	Health = UpdatedHealth;

	OnHealthChanged.Broadcast(Health, HealthDelta);
}



