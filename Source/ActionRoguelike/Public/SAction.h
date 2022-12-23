// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "SAction.generated.h"


class UWorld;
/**
 * 
 */
UCLASS(Blueprintable)
class ACTIONROGUELIKE_API USAction : public UObject
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable, Category = "Action")
		USActionComponent* GetOwningComponent() const;


	UPROPERTY(EditDefaultsOnly, Category = "Tags")
		FGameplayTagContainer GrantsTags;

	UPROPERTY(EditDefaultsOnly, Category = "Tags")
		FGameplayTagContainer BlockedTags;

public:

		UPROPERTY(EditDefaultsOnly, Category = "Action")
		FName ActionName;

		UFUNCTION(BlueprintNativeEvent, Category = "Action")
			void StartAction(AActor* Instigator);

		UFUNCTION(BlueprintNativeEvent, Category = "Action")
			void StopAction(AActor* Instigator);

		UWorld* GetWorld() const override;
};
