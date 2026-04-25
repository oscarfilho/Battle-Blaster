// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

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
	
	AActor* MyOwner = GetOwner();
	MyOwner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnDamageTaken);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::OnDamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("HealthComponent::OnDamageTaken called"));
	if (Damage >= 0.0f) {
		Health -= Damage;

		if (Health <= 0.0f) {
			UE_LOG(LogTemp, Warning, TEXT("The Actor %s has died!"), *DamagedActor->GetActorNameOrLabel());
			GetOwner()->Destroy();
		}
	}
}

