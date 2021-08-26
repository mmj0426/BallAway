// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "Blueprint/UserWidget.h"
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class BALLAWAY_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()

protected :

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* SoundButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* HomeButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ReplayButton;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UButton* ResumeButton;

	UFUNCTION()
	void OnSoundBtnTouched();

	UFUNCTION()
	void OnHomeBtnTouched();

	UFUNCTION()
	void OnReplayBtnTouched();

	UFUNCTION()
	void OnResumeBtnTouched();

public : 

	virtual void NativeConstruct() override;
};
