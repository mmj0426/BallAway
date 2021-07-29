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

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UScoreWidget> PlayScoreWidget;

	UScoreWidget* GetPlayScoreWidget();

private : 
	UPROPERTY()
	class UScoreWidget* PlayScoreText;
};
