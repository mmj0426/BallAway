// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BAHUD.h"
#include "UI/InGameWidget.h"
#include "UI/GameResultWidget.h"
#include "UI/PauseWidget.h"

ABAHUD::ABAHUD()
{

}

void ABAHUD::BeginPlay()
{
	Super::BeginPlay();

	if (InGameWidgetClass)
	{
		InGameWidget = CreateWidget<UInGameWidget>(GetWorld(), InGameWidgetClass);
		if (InGameWidget)
		{
			InGameWidget->AddToViewport();
		}
	}

	if (GameResultWidgetClass)
	{
		GameResultWidget = CreateWidget<UGameResultWidget>(GetWorld(), GameResultWidgetClass);
	}

	if (PauseMenuWidgetClass)
	{
		PauseMenuWidget = CreateWidget<UPauseWidget>(GetWorld(), PauseMenuWidgetClass);
	}
}

UInGameWidget* ABAHUD::GetInGameWidget()
{
	return InGameWidget;
}

UGameResultWidget* ABAHUD::GetGameResultWidget()
{
	return GameResultWidget;
}

UPauseWidget* ABAHUD::GetPauseMenuWidget()
{
	return PauseMenuWidget;
}
