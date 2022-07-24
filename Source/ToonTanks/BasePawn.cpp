// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Components/CapsuleComponent.h"
#include "Projectile.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleCollider"));
	RootComponent = CapsuleComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
	
}

void ABasePawn::HandleDestruction()
{
	if(DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}

	if (DeathParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticles, GetActorLocation(), GetActorRotation());
	}

	if(DeathSound)
	{
		UGameplayStatics::SpawnSoundAtLocation(this, DeathSound, GetActorLocation());
	}
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0, ToTarget.Rotation().Yaw, 0);
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(),LookAtRotation,UGameplayStatics::GetWorldDeltaSeconds(this),TurretRInterpRate));
}


void ABasePawn::RotateTurret(float Value)
{
	FRotator DeltaRotator = FRotator::ZeroRotator;
	DeltaRotator.Yaw = Value * TurretTurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	GetTurretMesh()->AddLocalRotation(DeltaRotator, true);
}

void ABasePawn::Fire()
{
	FVector Location = ProjectileSpawnPoint->GetComponentLocation();	
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);  // Set owner of the projectile
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UStaticMeshComponent* ABasePawn::GetTurretMesh()
{
	return TurretMesh;
}

//// Called to bind functionality to input
//void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
//	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

