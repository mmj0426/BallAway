
#pragma once

#include "../BallAway.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class BALLAWAY_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	float ScoreText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* CopyrightButton;

	UFUNCTION()
	void OnCopyrightTouched();

	UFUNCTION()
	void SetBestScoreText(float CurrentScore);

public:
	virtual void NativeConstruct() override;
};
