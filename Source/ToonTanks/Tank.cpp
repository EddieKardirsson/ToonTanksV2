// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"


ATank::ATank()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(MoveForwardName, this, &ATank::Move);
	PlayerInputComponent->BindAxis(TurnName, this, &ATank::Turn);
	PlayerInputComponent->BindAxis(RotateTurretName, this, &ABasePawn::RotateTurret);
}

void ATank::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(PlayerController)
	{
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, 
			false, HitResult);

		DrawDebugSphere(GetWorld(),
			HitResult.ImpactPoint + FVector(0, 0, 20),
			25, 20,
			FColor::Red, false);

		/*RotateTurret(HitResult.ImpactPoint);*/
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = Cast<APlayerController>(GetController());
}

void ATank::Move(float Value)
{
	FVector DeltaLocation=FVector::ZeroVector;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	FRotator DeltaRotator = FRotator::ZeroRotator;
	DeltaRotator.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotator, true);
}

void ATank::ControllerBoundTurretControls(float Value)
{
	RotateTurret(Value);
}

