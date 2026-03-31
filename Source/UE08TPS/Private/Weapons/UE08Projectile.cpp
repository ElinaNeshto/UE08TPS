// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/UE08Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"


// 
AUE08Projectile::AUE08Projectile()
{
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent=CreateDefaultSubobject<USphereComponent>("Sphere Component");
	CollisionComponent->InitSphereRadius(5.0f);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetRootComponent(CollisionComponent);

	MovementComponent=CreateDefaultSubobject<UProjectileMovementComponent>("Movement Component");
	MovementComponent->InitialSpeed = 3000.0f;
	MovementComponent->ProjectileGravityScale = 0.0f;
}

// 
void AUE08Projectile::BeginPlay()
{
	Super::BeginPlay();
	
	check(CollisionComponent);
	check(MovementComponent);

	CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
	CollisionComponent->OnComponentHit.AddDynamic(this, &AUE08Projectile::OnProjectileHit);

	SetLifeSpan(LifeSeconds);
}


//
void AUE08Projectile::OnProjectileHit(UPrimitiveComponent* HitComponent,
										AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse,
										const FHitResult& Hit)
{
	if (!GetWorld())
		return;

	MovementComponent->StopMovementImmediately();

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), DamageRadius, DamageType, {GetOwner()}, this, GetController(), bDoFullDamage);

	Destroy();
}

AController* AUE08Projectile::GetController() const
{
	const auto lPawn = Cast<APawn>(GetWorld());
	return lPawn ? lPawn->GetController() : nullptr;
}

