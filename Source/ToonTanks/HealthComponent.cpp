// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	AActor* OwnerActor = GetOwner();
	OwnerActor->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}


void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser)
{
	if (Health <= 0) return; 

	Health -= Damage;
	UE_LOG(LogTemp, Display, TEXT("Calling UHealthComponent::DamageTaken - Health: %f"), Health);
	if (Health <= 0 && ToonTanksGameMode)
	{
		UE_LOG(LogTemp, Warning, TEXT("Calling AToonTankGameMode::ActorDied"));
		ToonTanksGameMode->ActorDied(DamagedActor);
	}
	UE_LOG(LogTemp, Error, TEXT("Failed calling AToonTankGameMode::ActorDied"));
}

// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

