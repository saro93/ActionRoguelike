// Fill out your copyright notice in the Description page of Project Settings.

#include "SMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SAttributeComponent.h"
#include "Components/AudioComponent.h"
#include "particles/ParticleSystemComponent.h"
#include "SGameplayFunctionLibrary.h"
#include "SBaseProjectile.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{

	SphereComp->SetSphereRadius(20.0f);
	InitialLifeSpan = 10.0f;

	//SphereComp->OnComponentHit.AddDynamic(this, &ASMagicProjectile::OnHit);
	ProjectileDamage = 30;
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
}

void ASMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOverlap);
}

void ASMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetInstigator(OverlappedComponent->GetOwner()->GetInstigator());

	if (OtherActor && OtherActor != GetInstigator()) {
		UE_LOG(LogTemp, Warning, TEXT("Overlapped"));
		
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));
		/*if (AttributeComp) {

			AttributeComp->ApplyHealthChange(GetInstigator(), -ProjectileDamage);
			Destroy();
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), HitSound, this->GetActorLocation());
		}*/
			

		if (USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, ProjectileDamage, SweepResult))
		{
			Explode();
		}
	}


}



