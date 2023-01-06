// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SAttributeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnHealthChanged, AActor*,InstigatorActor, USAttributeComponent*,OwningComp, float, NewHealth, float, Delta);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROGUELIKE_API USAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UFUNCTION(BlueprintCallable,Category="Attributes")
	static USAttributeComponent* GetAttribute(AActor* FromActor );

	UFUNCTION(BlueprintCallable, Category = "Attributes", meta = (Display="IsAlive"))
	static bool IsActorAlive(AActor* Actor);

	// Sets default values for this component's properties
	USAttributeComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,Replicated, Category = "Attribute")
	    float Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "Attribute")
		float Max_Health;

	//UPROPERTY(NetMulticast, Reliable)
	//	bool bIsAlive;

	UFUNCTION(NetMulticast, Reliable) // @note: could mark as unreliable once we moved the 'state' out of scharacter (eg. once its cosmetic only)
		void MulticastHealthChanged(AActor* InstigatorActor, float NewHealth, float Delta);

public:	

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UFUNCTION(BlueprintCallable)
		bool IsAlive() const;

	UFUNCTION(BlueprintCallable, Category="Attribute")
	bool ApplyHealthChange(AActor* InstigatorActor,float Delta);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetHealthMax() const;

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		bool IsFullHealth() const;

	UFUNCTION(BlueprintCallable)
	bool Kill(AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable, Category = "Attributes")
		float GetHealth() const;
};
