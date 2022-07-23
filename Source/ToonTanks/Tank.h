// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:

	ATank();

	
public:

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = true))
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = true))
	float Speed = 600;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = true))
	float TurnRate = 100;

	

	void Move(float Value);
	void Turn(float Value);
	void ControllerBoundTurretControls(float Value);

	UPROPERTY()
	APlayerController* PlayerController;

	const FName FireName = TEXT("Fire");
	const FName MoveForwardName = TEXT("MoveForward");
	const FName TurnName = TEXT("Turn");
	const FName RotateTurretName = TEXT("RotateTurret");
};
