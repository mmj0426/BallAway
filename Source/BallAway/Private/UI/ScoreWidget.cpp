// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreWidget.h"
#include "GameMode/GM_InGame.h"


void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();
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