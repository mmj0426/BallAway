
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UButton* GameStartButton;

	UFUNCTION()
	void OnCopyrightTouched();

	UFUNCTION()
	void OnGameStartTouched();

public:
	virtual void NativeConstruct() override;
};
