
#include "UI/MainMenuWidget.h"
#include "UI/CopyrightWidget.h"
#include "GameMode/GM_MainMenu.h"
#include "UI/MainMenuHUD.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::OnCopyrightTouched()
{
	auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	auto HUD = Cast<AMainMenuHUD>(Controller->GetHUD());
	auto CopyrightWidget = (Cast<AMainMenuHUD>(Controller->GetHUD()))->GetCopyrightWidget();
	FInputModeUIOnly UIOnly;

	CopyrightWidget->AddToViewport();
}

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (CopyrightButton)
	{
		CopyrightButton->OnClicked.AddDynamic(this, &UMainMenuWidget::OnCopyrightTouched);
	}
}

void UMainMenuWidget::SetBestScoreText(float CurrentScore)
{
	auto GameMode = Cast<AGM_MainMenu>(GetWorld()->GetAuthGameMode());

	ScoreText = GameMode->BestScore;

	BALOG(Warning, TEXT("ScoreText : %f"), ScoreText);
}
