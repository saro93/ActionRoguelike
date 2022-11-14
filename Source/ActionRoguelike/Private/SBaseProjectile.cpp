// Fill out your copyright notice in the Description page of Project Settings.


#include "SBaseProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASBaseProjectile::ASBaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment( RootComponent);


	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 1000.0f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = false;

	InternalSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InternalSphere"));
	InternalSphere->SetSphereRadius(200);
	InternalSphere->SetupAttachment(RootComponent);
	InternalSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InternalSphere->OnComponentBeginOverlap.AddDynamic(this, &ASBaseProjectile::OnActorOverlap);

	RadialForce = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialComp"));
	RadialForce->SetupAttachment(Mesh);

	RadialForce->bIgnoreOwningActor = true;
	RadialForce->bAutoActivate = false;
	RadialForce->ImpulseStrength = -1000;
	RadialForce->ForceStrength = -2000000;
	RadialForce->Radius = 3000;
	RadialForce->Falloff = RIF_Constant;

}

// Called when the game starts or when spawned
void ASBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void ASBaseProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherComp->IsSimulatingPhysics()) { OtherActor->Destroy(); }
	DrawDebugString(GetWorld(),OtherActor->GetActorLocation(),TEXT("Ciao"),OtherActor,FColor::Red);
}



