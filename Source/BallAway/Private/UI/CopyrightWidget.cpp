// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CopyrightWidget.h"

#include "Components/Button.h"

void UCopyrightWidget::OnResumeButtonTouched()
{
	RemoveFromParent();
}

void UCopyrightWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton)
	{
		ResumeButton->OnClicked.AddDynamic(this, &UCopyrightWidget::OnResumeButtonTouched);
	}
}
