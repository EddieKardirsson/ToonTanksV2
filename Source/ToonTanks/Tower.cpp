// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"
#include "TimerManager.h"

ATower::ATower()
{
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	if(Tank)
	{
		
	}

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//if(Tank)
	//{
	//	float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	//	if(Distance <= FireRange)
	//	{
	//		RotateTurret(Tank->GetActorLocation());
	//	}
	//}

	if(CheckIfTankIsInFireRange())
	{
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::CheckFireCondition()
{
	//if(Tank)
	//{
	//	float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
	//	if(Distance <= FireRange)
	//	{
	//		Fire();
	//	}
	//}

	if(CheckIfTankIsInFireRange())
	{
		Fire();
	}
}

bool ATower::CheckIfTankIsInFireRange() const
{	
	if(Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if(Distance <= FireRange)
		{
			return true;
		}
	}
	return false;
}
