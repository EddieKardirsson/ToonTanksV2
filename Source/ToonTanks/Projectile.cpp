// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundBase.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	RootComponent = StaticMeshComponent;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	MovementComponent->InitialSpeed = InitialSpeed;
	MovementComponent->MaxSpeed = MaxSpeed;
	
	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("TrailParticles"));
	TrailParticles->SetupAttachment(RootComponent);
	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	StaticMeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	if(LaunchSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, LaunchSound, GetActorLocation());
	}
}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent,	FVector NormalImpulse, const FHitResult& Hit)
{
	const auto MyOwner = GetOwner();	
	if (!MyOwner)
	{
		Destroy();
		return;
	}
	const auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	if (!MyOwnerInstigator) return;

	UClass* DamageTypeClass = UDamageType::StaticClass();

	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		if(HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
		}
		if (HitSound)
		{
			UGameplayStatics::SpawnSoundAtLocation(this, HitSound, GetActorLocation());
		}
	}
	Destroy();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



