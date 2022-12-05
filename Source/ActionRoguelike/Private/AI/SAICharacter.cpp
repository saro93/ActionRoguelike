// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "SAttributeComponent.h"
#include "BrainComponent.h"

// Sets default values
ASAICharacter::ASAICharacter()
{
    PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");

    AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    TimeToHit = "TimeToHit";
}

void ASAICharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    PawnSensingComponent->OnSeePawn.AddDynamic(this, &ASAICharacter::OnPawnSeen);
    AttributeComp->OnHealthChanged.AddDynamic(this, &ASAICharacter::OnHealthChanged);

}

void ASAICharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwingComp, float NewHealth, float Delta)
{
    if (Delta < 0.0f) 
    {
       
        if (InstigatorActor != this)
        {
            SetTargetActor(InstigatorActor);
        }

        GetMesh()->SetScalarParameterValueOnMaterials(TimeToHit, GetWorld()->TimeSeconds);

        if (NewHealth <= 0.0f) 
        {
            AAIController* AIC = Cast<AAIController>(GetController());
            if (AIC)
            {
                AIC->GetBrainComponent()->StopLogic("Killed");
            }

            GetMesh()->SetAllBodiesSimulatePhysics(true);
            GetMesh()->SetCollisionProfileName("Ragdoll");

            SetLifeSpan(10.0f);
        }
    }

}


void ASAICharacter::SetTargetActor(AActor* NewTarget)
{
    AAIController* AIC = Cast<AAIController>(GetController());
    if (AIC) {
        AIC->GetBlackboardComponent()->SetValueAsObject("TargetActor", NewTarget);
    }
}


void ASAICharacter::OnPawnSeen(APawn* Pawn)
{
    SetTargetActor(Pawn);
        DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.0f, true);

}


