// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

ATower::ATower()
{
	UE_LOG(LogTemp, Display, TEXT("Tower constructor was called!"));
}


void ATower::BeginPlay()
{
	Super::BeginPlay();
}


void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	double DistanceToTank = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());
	
	if (DistanceToTank <= FireRange) {
		UE_LOG(LogTemp, Display, TEXT("Tank is at sight! FIREEEE"));
		RotateTurret(Tank->GetActorLocation());
	}


	RotateTurret(Tank->GetActorLocation());
}

