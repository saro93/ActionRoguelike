// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractionComponent.h"
#include "SGameplayInterface.h"
#include "DrawDebugHelpers.h"
#include "SWorldUserWidget.h"

static TAutoConsoleVariable<bool> CVarDebugDrawInteraction(TEXT("su.InteractionDebugDraw"), false, TEXT("Enable Debug Lines for Interact Component"), ECVF_Cheat);


// Sets default values for this component's properties
USInteractionComponent::USInteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	PrimaryComponentTick.TickGroup = TG_PostUpdateWork;


	TraceRadius = 30.0f;
	TraceDistance = 500.0f;
	CollisionChannel = ECC_WorldDynamic;
	// ...
}


// Called when the game starts
void USInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



void USInteractionComponent::ClearInteractUI()
{
	FocusedActor = nullptr;

	if (DefaultWidgetInstance)
	{
		DefaultWidgetInstance->RemoveFromParent();
		DefaultWidgetInstance->AttachedActor = nullptr;
		DefaultWidgetInstance = nullptr;
	}
}

void USInteractionComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ClearInteractUI();
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void USInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (MyPawn && MyPawn->IsLocallyControlled())
	{
		FindBestInteractable();
	}
	
}

void USInteractionComponent::FindBestInteractable()
{
	bool bDebugDraw = CVarDebugDrawInteraction.GetValueOnGameThread();

	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(CollisionChannel);

	AActor* MyOwner = GetOwner();

	FVector EyeLocation;
	FRotator EyeRotation;
	MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

	FVector End = EyeLocation + (EyeRotation.Vector() * TraceDistance);
	//FHitResult Hit;
	//bool bBlockingHit =  GetWorld()->LineTraceSingleByObjectType(Hit,EyeLocation, End, ObjectQueryParams);

	TArray<FHitResult> Hits;

	FCollisionShape Shape;
	Shape.SetSphere(TraceRadius);

	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, Shape);

	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	//clear before trying to fill
	FocusedActor = nullptr;

	for (FHitResult Hit : Hits) {

		if (bDebugDraw) {

			DrawDebugSphere(GetWorld(), Hit.ImpactPoint, TraceRadius, 32, LineColor, false, 2.0f);
		}

		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<USGameplayInterface>()) {

				FocusedActor = HitActor;
				break;
			}
		}

	}

	if (FocusedActor) 
	{
		if(DefaultWidgetInstance == nullptr && ensure(DefaultWidgetClass))
		{
			DefaultWidgetInstance = CreateWidget<USWorldUserWidget>(GetWorld(), DefaultWidgetClass);
		}
		
		if (DefaultWidgetInstance) {
			
			DefaultWidgetInstance->AttachedActor = FocusedActor;

			if (!DefaultWidgetInstance->IsInViewport())
			{
				DefaultWidgetInstance->AddToViewport();
			}
		}

	}
	else {
		if (DefaultWidgetInstance) {
			ClearInteractUI();
		}
	}

	if (bDebugDraw)
		DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.0f, 0, 2.0f);
}


void USInteractionComponent::PrimaryInteract()
{
	if (FocusedActor == nullptr)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("No Focus Actor to Interact"));
		}
		return;
	}

	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (!MyPawn)
	{
		return;
	}

	// Chiamata solo sul server (lato client invia RPC)
	ServerInteract(FocusedActor);
}




void USInteractionComponent::ServerInteract_Implementation(AActor* InFocus)
{
	if (!InFocus)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("No Focus Actor to Interact"));
		}
		return;
	}

	if (!InFocus->Implements<USGameplayInterface>())
	{
		return;
	}

	APawn* MyPawn = Cast<APawn>(GetOwner());
	if (!MyPawn)
	{
		return;
	}

	ISGameplayInterface::Execute_Interact(InFocus, MyPawn);

}