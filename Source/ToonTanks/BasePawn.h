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



	UPROPERTY(VisibleInstanceOnly, Category = "MockupProperties")
	int32 VisibleInstanceOnlyInteger = 14;

	UPROPERTY(VisibleDefaultsOnly, Category = "MockupProperties")
	int32 VisibleDefaultsOnlyInteger = 5;

	UPROPERTY(EditDefaultsOnly, Category = "MockupProperties")
	int32 EditDefaultsOnlyInteger = 9;

	UPROPERTY(EditInstanceOnly, Category = "MockupProperties")
	int32 EditInstanceOnlyInteger = 11;

	UPROPERTY(EditAnywhere)
	float Speed = 400;
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MockupProperties", meta = (AllowPrivateAccess = true))
	int32 VisibleAnywhereInteger = 69;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MockupProperties", meta = (AllowPrivateAccess = true))
	int32 EditAnywhereInteger = 13;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
