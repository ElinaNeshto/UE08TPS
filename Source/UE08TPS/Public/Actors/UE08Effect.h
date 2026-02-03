// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "UE08Effect.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogUE08Effect, All, All)

UCLASS()
class UE08TPS_API AUE08Effect : public AActor
{
	GENERATED_BODY()
	
public:	

	AUE08Effect();


	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void ComponentName(UNiagaraComponent* Niagara);


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ChangeParametrs(UNiagaraComponent* Niagara);
	void ChangeParametrs_Implementation(UNiagaraComponent* Niagara);

	UFUNCTION(BlueprintCallable)
	void Component(UNiagaraComponent*& Niagara);


protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UNiagaraComponent* NiagaraSystem;

};
