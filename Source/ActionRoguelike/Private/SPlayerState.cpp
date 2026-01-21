// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"
#include "SSaveGame.h"


void ASPlayerState::AddCredits(int32 Delta)
{
	// Avoid User-error of adding a negative amount or zero
	if (!ensure(Delta > 0.0f)) {
		return;
	}

	Credits += Delta;

	OnCreditsChanged.Broadcast(this, Credits,Delta);
}

bool ASPlayerState::RemoveCredits(int32 Delta)
{
	// Avoid User-error of adding a negative amount or zero
	if (!ensure(Delta > 0.0f)) {
		return false;
	}
	if (Credits < Delta) 
	{
		//Not enough credits available
		return false;
	}

	Credits -= Delta;

	OnCreditsChanged.Broadcast(this,Credits,-Delta);

	return true;

}

void ASPlayerState::SavePlayerState(USSaveGame* SaveObject)
{
	if (SaveObject)
	{
		SaveObject->Credits = Credits;
	}
}

void ASPlayerState::LoadPlayerState(USSaveGame* SaveObject)
{
	if (SaveObject)
	{
		Credits = SaveObject->Credits;
	}
}

void ASPlayerState::OnRep_Credits(int32 OldCredits)
{
	OnCreditsChanged.Broadcast(this, Credits, Credits - OldCredits);
}

int32 ASPlayerState::GetCredits() const
{
	return Credits;
}