// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:

	ATower();

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float DeltaSeconds) override;

	void HandleDestruction();

private:

	UPROPERTY()
	class ATank* Tank;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	float FireRange = 800;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2;

	void CheckFireCondition();

	bool CheckIfTankIsInFireRange() const;
	
};
