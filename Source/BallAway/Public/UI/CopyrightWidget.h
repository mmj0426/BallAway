// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "Blueprint/UserWidget.h"
#include "CopyrightWidget.generated.h"

/**
 * 
 */
UCLASS()
class BALLAWAY_API UCopyrightWidget : public UUserWidget
{
	GENERATED_BODY()
public : 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* ResumeButton;

	UFUNCTION()
	void OnResumeButtonTouched();

	virtual void NativeConstruct() override;
};
