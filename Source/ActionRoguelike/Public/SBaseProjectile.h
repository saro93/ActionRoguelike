// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UAudioComponent;


UCLASS(ABSTRACT) // 'ABSTRACT' marks this class as incomplete, keeping this out of certain dropdowns windows like SpawnActor in Unreal Editor
class ACTIONROGUELIKE_API ASBaseProjectile : public AActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* ImpactVFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UProjectileMovementComponent* MoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UParticleSystemComponent* EffectComp;

	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComp;


	// 'virtual' so we can override this in child-classes
	UFUNCTION()
		virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// BlueprintNativeEvent = C++ base implementation, can be expanded in Blueprints
	// BlueprintCallable to allow child classes to trigger explosions
	// Not required for assignment, useful for expanding in Blueprint later on
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Explode();

	virtual void PostInitializeComponents() override;

public:



	ASBaseProjectile();

};