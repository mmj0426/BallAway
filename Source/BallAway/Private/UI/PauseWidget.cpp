// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UPauseWidget::OnSoundBtnTouched()
{
}

void UPauseWidget::OnHomeBtnTouched()
{
	//UGameplayStatics::OpenLevel(GetWorld(),TEXT("Cute_Zoo_3_Map"));
}

void UPauseWidget::OnReplayBtnTouched()
{
	UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),TEXT("RestartLevel"));
	//UGameplayStatics::OpenLevel(GetWorld(),TEXT("Default"));
}

void UPauseWidget::OnResumeBtnTouched()
{
	UGameplayStatics::SetGamePaused(GetWorld(), false);

	RemoveFromParent();
}

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (SoundButton)
	{
		SoundButton->OnClicked.AddDynamic(this, &UPauseWidget::OnSoundBtnTouched);
	}

	if (HomeButton)
	{
		HomeButton->OnClicked.AddDynamic(this, &UPauseWidget::OnHomeBtnTouched);
	}

	if (ReplayButton)
	{
		ReplayButton->OnClicked.AddDynamic(this, &UPauseWidget::OnReplayBtnTouched);
	}

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UPauseWidget::OnResumeBtnTouched);
	}
}
