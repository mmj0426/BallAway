
#include "UI/InGameWidget.h"
#include "UI/BAHUD.h"
#include "UI/PauseWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "GameMode/GM_InGame.h"

void UInGameWidget::SetPlayScoreText(float CurrentScore)
{
	PlayScoreText = CurrentScore;
}

void UInGameWidget::OnPauseTouched()
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);

	auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto HUD = Cast<ABAHUD>(Controller->GetHUD());
	auto PauseMenuWidget = (Cast<ABAHUD>(Controller->GetHUD()))->GetPauseMenuWidget();
	FInputModeUIOnly UIOnly;

	PauseMenuWidget->AddToViewport();
}

void UInGameWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (PauseButton)
	{
		PauseButton->OnClicked.AddDynamic(this, &UInGameWidget::OnPauseTouched);
	}

	UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(), 0), this);
}
