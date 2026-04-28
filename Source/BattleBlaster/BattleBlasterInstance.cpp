// Fill out your copyright notice in the Description page of Project Settings.


#include "BattleBlasterInstance.h"
#include "Kismet/GameplayStatics.h"

void UBattleBlasterInstance::ChangeLevel(uint32 LevelIndex)
{
	if (CurrentLevelIndex >= LastLevelIndex && CurrentLevelIndex > 0) {
		UE_LOG(LogTemp, Display, TEXT("CurrentLevelIndex: %d, LastLevelIndex: %d"), CurrentLevelIndex, LastLevelIndex);
		return;
	}
	else {
		CurrentLevelIndex = LevelIndex;
		FString NewLevel = FString::Printf(TEXT("Level_%d"), CurrentLevelIndex);
		UE_LOG(LogTemp, Display, TEXT("Changing to the level: %s"), *NewLevel);
		UGameplayStatics::OpenLevel(GetWorld(), FName(*NewLevel));
	}
}

void UBattleBlasterInstance::LoadNextLevel()
{
	if(CurrentLevelIndex < LastLevelIndex) 
	{
		ChangeLevel(CurrentLevelIndex + 1);
	}
	else
		RestartGame();
}

void UBattleBlasterInstance::RestartCurrentLevel()
{
	ChangeLevel(CurrentLevelIndex);
}

void UBattleBlasterInstance::RestartGame()
{
	CurrentLevelIndex = 1;
	ChangeLevel(CurrentLevelIndex);
}