
#include "UI/GameResultWidget.h"
#include "GameMode/GM_InGame.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UGameResultWidget::SetPlayScoreText()
{
	auto GameMode = Cast<AGM_InGame>(GetWorld()->GetAuthGameMode());

	PlayScoreText = GameMode->PlayScore;
}

void UGameResultWidget::SetBestScoreText()
{
	auto GameMode = Cast<AGM_InGame>(GetWorld()->GetAuthGameMode());

	BestScoreText = GameMode->BestScore;
}

void UGameResultWidget::OnHomeBtnTouched()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Main"));
}

void UGameResultWidget::OnReplayBtnTouched()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), TEXT("RestartLevel"));
}

void UGameResultWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (HomeButton)
	{
		HomeButton->OnClicked.AddDynamic(this, &UGameResultWidget::OnHomeBtnTouched);
	}

	if (ReplayButton)
	{
		ReplayButton->OnClicked.AddDynamic(this, &UGameResultWidget::OnHomeBtnTouched);
	}
}
