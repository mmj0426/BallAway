// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "GameFramework/HUD.h"
#include "BAHUD.generated.h"

class UGameResultWidget;
class UInGameWidget;
class UPauseWidget;

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

	// InGame UI
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UInGameWidget> InGameWidgetClass;

	// Game Result UI
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UGameResultWidget> GameResultWidgetClass;

	// PauseMenu
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UPauseWidget> PauseMenuWidgetClass;

	UInGameWidget* GetInGameWidget();
	UGameResultWidget* GetGameResultWidget();
	UPauseWidget* GetPauseMenuWidget();

private : 
	UPROPERTY()
	class UInGameWidget* InGameWidget;

	UPROPERTY()
	class UGameResultWidget* GameResultWidget;

	UPROPERTY()
	class UPauseWidget* PauseMenuWidget;
};
