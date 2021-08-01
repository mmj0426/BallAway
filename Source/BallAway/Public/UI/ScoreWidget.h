// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "Blueprint/UserWidget.h"
#include "ScoreWidget.generated.h"

/**
 * 
 */
UCLASS()
class BALLAWAY_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()
	
public : 
	virtual void NativeConstruct() override;

	 void SetPlayScoreText(float CurrentScore);
	 void GetBestScoreText();

	 UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	 float PlayScoreText;

	 UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	 float BestScoreText;
};