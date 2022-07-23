// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

#include "Tank.h"

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
}

void ATower::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
		if(Distance <= FireRange)
		{
			RotateTurret(Tank->GetActorLocation());
		}
	}
}
