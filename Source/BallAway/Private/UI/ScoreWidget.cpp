// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreWidget.h"

void UScoreWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UScoreWidget::SetPlayScore(float CurrentScore)
{
	PlayScore = CurrentScore;
}
