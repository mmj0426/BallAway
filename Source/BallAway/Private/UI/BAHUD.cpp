// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/BAHUD.h"
#include "UI/ScoreWidget.h"

ABAHUD::ABAHUD()
{

}

void ABAHUD::BeginPlay()
{
	Super::BeginPlay();

	if (PlayScoreWidget)
	{
		PlayScoreText = CreateWidget<UScoreWidget>(GetWorld(), PlayScoreWidget);
		if (PlayScoreText)
		{
			PlayScoreText->AddToViewport();
		}
	}

	if (GameResultWidget)
	{
		ResultScoreText = CreateWidget<UScoreWidget>(GetWorld(), GameResultWidget);
	}
}

UScoreWidget* ABAHUD::GetPlayScoreWidget()
{
	return PlayScoreText;
}

UScoreWidget* ABAHUD::GetGameResultWidget()
{
	return ResultScoreText;
}
