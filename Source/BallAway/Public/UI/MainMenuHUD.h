
#pragma once

#include "../BallAway.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

class UMainMenuWidget;
class UCopyrightWidget;

/**
 * 
 */
UCLASS()
class BALLAWAY_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
public:

	virtual void BeginPlay();

	// MainMenu UI
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

	// Copyright UI
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UCopyrightWidget> CopyrightWidgetClass;

	UMainMenuWidget* GetMainMenuWidget();
	UCopyrightWidget* GetCopyrightWidget();

private:
	UPROPERTY()
	class UMainMenuWidget* MainMenuWidget;

	UPROPERTY()
	class UCopyrightWidget* CopyrightWidget;

};
