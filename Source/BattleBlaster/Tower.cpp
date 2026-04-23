// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

ATower::ATower()
{
}


void ATower::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle FireRateTimerHandle;
	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireTimerInterval, true);
}


void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange()) {
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::CheckFireCondition()
{
	if(Tank && InFireRange()) {
		Fire();
	}
}


bool ATower::InFireRange() {
	if(Tank && FVector::Dist(Tank->GetActorLocation(), GetActorLocation()) <= FireRange) {
		return true;
	}
	return false;
}