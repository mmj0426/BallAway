
#include "UI/MainMenuHUD.h"
#include "UI/MainMenuWidget.h"
#include "UI/CopyrightWidget.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
		}
	}

	if (CopyrightWidgetClass)
	{
		CopyrightWidget = CreateWidget<UCopyrightWidget>(GetWorld(),CopyrightWidgetClass);
	}
}

UMainMenuWidget* AMainMenuHUD::GetMainMenuWidget()
{
	return MainMenuWidget;
}

UCopyrightWidget* AMainMenuHUD::GetCopyrightWidget()
{
	return CopyrightWidget;
}
