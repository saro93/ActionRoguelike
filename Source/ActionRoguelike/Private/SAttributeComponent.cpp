// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"

// Sets default values for this component's properties
USAttributeComponent::USAttributeComponent()
{
	Max_Health = 100;
	Health = Max_Health;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	if(Health>0){
		Health += Delta;
		OnHealthChanged.Broadcast(nullptr, this, Health, Delta);
		Health = FMath::Clamp(Health, 0, Max_Health);
	}

	return true;
}

float USAttributeComponent::GetHealthMax() const
{
	return Max_Health;
}

bool USAttributeComponent::IsFullHealth() const
{
	return Health == Max_Health;
}



