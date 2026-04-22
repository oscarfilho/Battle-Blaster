// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tower.h"

ABattleBlasterGameMode::ABattleBlasterGameMode()
{
	UE_LOG(LogTemp, Display, TEXT("ABattleBlasterGameMode was created! Called the constructor!"));
}

void ABattleBlasterGameMode::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundTowers;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATower::StaticClass(), FoundTowers);
	TowerCount = FoundTowers.Num();

	UE_LOG(LogTemp, Warning, TEXT("TowerCount: %d"), TowerCount);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (PlayerPawn) {
		Tank = Cast<ATank>(PlayerPawn);
		if (!Tank) {
			UE_LOG(LogTemp, Warning, TEXT("Tank HAS FAILED to casted!"));
		}
	}

	UE_LOG(LogTemp, Display, TEXT("Start of the loop: "));
	int32 LoopIndex = 0;

	while (LoopIndex < 10) 
	{
		UE_LOG(LogTemp, Display, TEXT("Body of the loop"));
		LoopIndex++;
	}

	UE_LOG(LogTemp, Display, TEXT("End of the loop "));


	for (int32 i = 0; i < TowerCount; i++)
	{
		auto& MyTower = FoundTowers[i];
		ATower* Tower = Cast<ATower>(MyTower);
		if (Tower && Tank) {
			Tower->Tank = Tank;
			Tower->RotateTurret(Tank->GetActorLocation());
			UE_LOG(LogTemp, Display, TEXT("Tower found: %s"), *Tower->GetName());
		}
	}

	/*for (AActor* MyActor: FoundTowers) {

		ATower* MyTower = Cast<ATower>(MyActor);
		if(MyTower) {
			UE_LOG(LogTemp, Display, TEXT("Tower found: %s"), *MyTower->GetName());
		}
	}*/


}

void ABattleBlasterGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}