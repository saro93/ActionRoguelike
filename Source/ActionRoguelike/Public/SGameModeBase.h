// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "SGameModeBase.generated.h"

class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;
class UCurveFloat;

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASGameModeBase();

	virtual void StartPlay() override;

	UFUNCTION(Exec)
		void KillAll();

	UFUNCTION()
		void RespawnPlayerElapsed(AController* Controller);

	virtual void OnActorkilled(AActor* VictimActor, AActor* Killer);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TSubclassOf<AActor> MinionClass;

	FTimerHandle TimerHandle_SpawnBots;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float SpawnTimerInterval;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		UEnvQuery* SpawnBotQuery;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UCurveFloat* DifficultyCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
		int32 CreditsPerKill;

	/* All power-up classes used to spawn with EQS at match start */
	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
		TArray<TSubclassOf<AActor>> PowerupClasses;

	/* Curve to grant credits to spend on spawning monsters */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		UCurveFloat* SpawnCreditCurve;

	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
		UEnvQuery* PowerupSpawnQuery;

	/* Time to wait between failed attempts to spawn/buy monster to give some time to build up credits. */
	UPROPERTY(EditDefaultsOnly, Category = "AI")
		float CooldownTimeBetweenFailures;

	/* Amount of powerups to spawn during match start */
	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
		int32 DesiredPowerupCount;

	/* Distance required between power-up spawn locations */
	UPROPERTY(EditDefaultsOnly, Category = "Powerups")
		float RequiredPowerupDistance;

	UFUNCTION()
	void SpawnBotTimerElapsed();

	UFUNCTION()
	void OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	UFUNCTION()
	void OnPowerupSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	// Points available to spend on spawning monsters
	float AvailableSpawnCredit;

};
