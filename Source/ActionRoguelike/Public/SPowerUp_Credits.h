// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerupActor.h"
#include "SPowerUp_Credits.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPowerUp_Credits : public ASPowerupActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Credits")
		int32 CreditsAmount;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;

	ASPowerUp_Credits();
	
};
