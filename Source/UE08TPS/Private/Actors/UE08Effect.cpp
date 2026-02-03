
#include "Actors/UE08Effect.h"
#include "NiagaraComponent.h"

DEFINE_LOG_CATEGORY(LogUE08Effect)

//
AUE08Effect::AUE08Effect()
{

	PrimaryActorTick.bCanEverTick = false;

	NiagaraSystem = CreateDefaultSubobject<UNiagaraComponent>("Niagara Effect");
	NiagaraSystem->SetupAttachment(RootComponent);

}

void AUE08Effect::ChangeParametrs_Implementation(UNiagaraComponent* Niagara)
{
	UE_LOG(LogUE08Effect, Error, TEXT("Component do not exist!"));
}

void AUE08Effect::Component(UNiagaraComponent*& Niagara)
{
	Niagara = NiagaraSystem;
}



 
void AUE08Effect::BeginPlay()
{
	Super::BeginPlay();
	
}


