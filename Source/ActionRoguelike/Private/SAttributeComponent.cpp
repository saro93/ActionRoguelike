// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"
#include "SGameModeBase.h"

static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultiplier"), 1.0f, TEXT("Global Damage modifier for attribute component."), ECVF_Cheat);

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Max_Health = 100;
	Health = Max_Health;

	SetIsReplicatedByDefault(true);
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}



float USAttributeComponent::GetHealthMax() const
{
	return Max_Health;
}

bool USAttributeComponent::IsFullHealth() const
{
	return Health == Max_Health;
}

bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetHealthMax());
}

float USAttributeComponent::GetHealth() const
{
	return Health;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();

		Delta *= DamageMultiplier;
	}

	float OldHealth = Health;
	Health = FMath::Clamp(Health + Delta, 0.0f, Max_Health);
	//NewHealth = FMath::Clamp(Health + Delta, 0, Max_Health);

	float ActualDelta = Health - OldHealth;

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);

	if (ActualDelta < 0.0f && Health == 0.0f) 
	{
		ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();
		if (GM) 
		{
			GM->OnActorkilled(GetOwner(), InstigatorActor);
		}
	}

	return ActualDelta != 0;
}

USAttributeComponent* USAttributeComponent::GetAttribute(AActor* FromActor)
{
	if (FromActor)
	{
		//return FromActor->FindComponentByClass<USAttributeComponent>();
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}

	return nullptr;
}

bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	USAttributeComponent* AttributeComp = GetAttribute(Actor);
	if (AttributeComp) {
		return AttributeComp->IsAlive();
	}

	return false;
}

void USAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
{
	OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta);
}


