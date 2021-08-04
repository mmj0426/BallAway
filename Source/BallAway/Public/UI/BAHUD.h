// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "GameFramework/HUD.h"
#include "BAHUD.generated.h"

class UScoreWidget;

/**
 * 
 */
UCLASS()
class BALLAWAY_API ABAHUD : public AHUD
{
	GENERATED_BODY()
	
public : 
	ABAHUD();

	virtual void BeginPlay();

	// 플레이 중 스코어
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UScoreWidget> PlayScoreWidget;

	// Load Best Score
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UScoreWidget> GameResultWidget;

	UScoreWidget* GetPlayScoreWidget();
	UScoreWidget* GetGameResultWidget();

private : 
	UPROPERTY()
	class UScoreWidget* PlayScoreText;

	UPROPERTY()
	class UScoreWidget* ResultScoreText;
};
