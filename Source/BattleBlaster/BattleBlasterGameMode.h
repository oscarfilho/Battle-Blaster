// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tank.h"
#include "ScreenMessage.h"
#include "BattleBlasterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ABattleBlasterGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UScreenMessage> ScreenMessageClass;
	UScreenMessage* ScreenMessageWidget;

	UPROPERTY(EditAnywhere, Category = "Game Loop")
	float GameOverOverlay = 3.0f;

	bool IsGameOver = false;
	bool IsVictory = false;

	UPROPERTY(Editanywhere, Category = "Game Loop")
	int32 CountdownDelay = 3;

	int32 CountdownSeconds;
	FTimerHandle CountdownTimerHandle;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	ATank* Tank;

	int32 TowerCount;

	void ActorDied(AActor* DeadActor);

	bool TowersHaveDestructed();
	void OnGameOverTimerTimeout();

	void OnCountdownTimerTimeout();
};
