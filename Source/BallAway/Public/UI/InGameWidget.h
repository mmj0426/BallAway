#pragma once

#include "../BallAway.h"
#include "Blueprint/UserWidget.h"
#include "InGameWidget.generated.h"


UCLASS()
class BALLAWAY_API UInGameWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected : 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	float PlayScoreText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* PauseButton;

	UFUNCTION()
	void OnPauseTouched();

public : 
	virtual void NativeConstruct() override;

	UFUNCTION()
	void SetPlayScoreText(float CurrentScore);
};
