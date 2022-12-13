// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameplayFunctionLibrary.h"
#include "SAttributeComponent.h"

bool USGameplayFunctionLibrary::ApplyDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount)
{
	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttribute(TargetActor);
	if (AttributeComp) {
		return AttributeComp->ApplyHealthChange(DamageCauser, -DamageAmount);
	}

	return false;
}

bool USGameplayFunctionLibrary::ApplyDirectionalDamage(AActor* DamageCauser, AActor* TargetActor, float DamageAmount, const FHitResult& Hitresult)
{
	if (ApplyDamage(DamageCauser, TargetActor, DamageAmount))
	{
		UPrimitiveComponent* HitComp = Hitresult.GetComponent();

		if (HitComp && HitComp->IsSimulatingPhysics(Hitresult.BoneName)) {
			HitComp->AddImpulseAtLocation(-Hitresult.ImpactNormal * 300000.f, Hitresult.ImpactPoint, Hitresult.BoneName);
		}
		return true;
	}

	return false;
}
