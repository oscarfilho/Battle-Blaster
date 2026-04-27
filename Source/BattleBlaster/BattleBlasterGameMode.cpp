// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BattleBlasterInstance.h"
#include "Tower.h"
#include "Tank.h"


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

	for (int32 i = 0; i < TowerCount; i++)
	{
		auto& MyTower = FoundTowers[i];
		ATower* Tower = Cast<ATower>(MyTower);
		if (Tower && Tank) {
			Tower->Tank = Tank;
			Tower->RotateTurret(Tank->GetActorLocation());
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

void ABattleBlasterGameMode::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Tank) {
		Tank->HandleDestruction();
		UE_LOG(LogTemp, Warning, TEXT("YOU LOSE!"));
		IsGameOver = true;
	}
	else {
		ATower* Tower = Cast<ATower>(DeadActor);
		if (Tower) {
			TowerCount--;
			Tower->HandleDestruction();
			UE_LOG(LogTemp, Warning, TEXT("TowerCount: %d"), TowerCount);
			IsGameOver = IsVictory = TowersHaveDestructed();
		}
	}

	if (IsGameOver) {
		FString GameOverMessage = IsVictory ? TEXT("Victory!") : TEXT("Defeat!");
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GameOverMessage);

		FTimerHandle GameOverTimerHandle;
		GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &ABattleBlasterGameMode::OnGameOverTimerTimeout, GameOverOverlay, false);
	}
}

bool ABattleBlasterGameMode::TowersHaveDestructed() {
	return TowerCount <= 0;
}

void ABattleBlasterGameMode::OnGameOverTimerTimeout()
{
	UE_LOG(LogTemp, Display, TEXT("Showing the game over timer overlay now..."));
	FString CurrentGameLevel = UGameplayStatics::GetCurrentLevelName(GetWorld());

	UGameInstance* GameInstance = GetGameInstance();
	UBattleBlasterInstance* BattleBlasterInstance = Cast<UBattleBlasterInstance>(GameInstance);
	if(BattleBlasterInstance) {
		UE_LOG(LogTemp, Warning, TEXT("BattleBlasterInstance found!"));
	}

	//if (IsVictory) {
	//	// Load the next level
	//	UGameplayStatics::OpenLevel(GetWorld(), *CurrentGameLevel, false);
	//}
	//else {
	//	// Reload the current level
	//	UGameplayStatics::OpenLevel(GetWorld(), *CurrentGameLevel, false);
	//}
	
}
