#pragma once

#include "../BallAway.h"
#include "Blueprint/UserWidget.h"
#include "GameResultWidget.generated.h"

UCLASS()
class BALLAWAY_API UGameResultWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected : 
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	float PlayScoreText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	float BestScoreText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* HomeButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* ReplayButton;
	
	UFUNCTION()
	void OnHomeBtnTouched();

	UFUNCTION()
	void OnReplayBtnTouched();

public : 
	virtual void NativeConstruct() override;

	UFUNCTION()
		void SetPlayScoreText();

	UFUNCTION()
		void SetBestScoreText();
};
