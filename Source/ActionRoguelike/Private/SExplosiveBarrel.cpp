// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"
#include "Components/SphereComponent.h"
#include "SMagicProjectile.h"
#include "SCharacter.generated.h"

// class FString;
// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName("PhysicsActor");
	Mesh->SetSimulatePhysics(true);
	Mesh->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnHit);

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialArea");
	RadialForce->SetupAttachment(Mesh);
	RadialForce->SetRelativeLocation(FVector(0,0,70));
	RadialForce->Radius = 750;
	RadialForce->ImpulseStrength = 2500;
	RadialForce->ForceStrength = 1000;
	RadialForce->bImpulseVelChange = true;
	RadialForce->bAutoActivate = false;
	RadialForce->SetAutoActivate(false);

}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASExplosiveBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

		Proiettile = Cast<ASMagicProjectile>(OtherActor);
		if (Proiettile) {
			RadialForce->FireImpulse();
		}

		// %s = string
		// %f = float
		// logs: "OtherActor": MyActor, at gametime: 124.4"
		UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at get time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

		FString CombinedString = FString::Printf(TEXT("Hit at location:"), *Hit.ImpactPoint.ToString());
		DrawDebugString(GetWorld(), Hit.ImpactPoint,CombinedString, nullptr, FColor::Green, 4.0f, true);
}

// Called every frame
void ASExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

