// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosiveBarrel.h"
#include "Components/SphereComponent.h"
#include "SMagicProjectile.h"
#include "SCharacter.generated.h"


// Sets default values
AExplosiveBarrel::AExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName("PhysicsActor");
	Mesh->SetSimulatePhysics(true);
	Mesh->OnComponentHit.AddDynamic(this, &AExplosiveBarrel::OnHit);

	RadialForce = CreateDefaultSubobject<URadialForceComponent>("RadialArea");
	RadialForce->SetupAttachment(Mesh);
	RadialForce->SetRelativeLocation(FVector(0,0,70));
	RadialForce->Radius = 500;
	RadialForce->ForceStrength = 2000;
	RadialForce->bImpulseVelChange = true;
	RadialForce->bAutoActivate = false;

}

// Called when the game starts or when spawned
void AExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExplosiveBarrel::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
		UE_LOG(LogTemp, Warning, TEXT("Hello"));
		Proiettile = Cast<ASMagicProjectile>(OtherActor);
		if (Proiettile) {
			RadialForce->FireImpulse();
		}
}

// Called every frame
void AExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

