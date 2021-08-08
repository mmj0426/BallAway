// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"
#include "GameMode/GM_InGame.h"


void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//if (PauseButton)
	//{
	//	PauseButton->OnClicked.AddDynamic(this,&UScoreWidget::OnPauseTouched);
	//}

	//UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(UGameplayStatics::GetPlayerController(GetWorld(),0),this);
}

void UScoreWidget::SetPlayScoreText(float CurrentScore)
{
	PlayScoreText = CurrentScore;
}

void UScoreWidget::GetBestScoreText()
{
	auto GameMode = Cast<AGM_InGame>(GetWorld()->GetAuthGameMode());

	BestScoreText =	GameMode->BestScore;
}

void UScoreWidget::OnPauseTouched()
{
	//UGameplayStatics::SetGamePaused(GetWorld(), true);
}
