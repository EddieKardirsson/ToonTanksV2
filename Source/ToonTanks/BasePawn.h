// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void RotateTurret(FVector LookAtTarget);
public:
	void RotateTurret(float Value);

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = true))
	float TurretTurnRate = 150;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = true))
	float TurretRInterpRate = 5;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:

	UFUNCTION()
	UStaticMeshComponent* GetTurretMesh();
};
