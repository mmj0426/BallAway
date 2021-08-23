
#include "GameMode/GM_MainMenu.h"
#include "UI/MainMenuHUD.h"

#include "BallAway/Public/GameMode/BASaveGame.h"
#include "Kismet/GameplayStatics.h"

AGM_MainMenu::AGM_MainMenu()
{
	// HUD
	static ConstructorHelpers::FClassFinder<AMainMenuHUD>
	HudClass(TEXT("/Game/UI/BP_MainMenuHUD.BP_MainMenuHUD_C"));

	HUDClass = HudClass.Class;

	BestScore = LoadScore();
	//BALOG(Warning, TEXT("BestScore : %f"), BestScore);
}

float AGM_MainMenu::LoadScore()
{
	UBASaveGame* LoadGameInstance = Cast<UBASaveGame>(UGameplayStatics::CreateSaveGameObject(UBASaveGame::StaticClass()));

	if (LoadGameInstance)
	{
		LoadGameInstance->SaveSlotName = "SaveGame";
		LoadGameInstance->SaveIndex = 0;

		LoadGameInstance = Cast<UBASaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->SaveIndex));
		if (nullptr == LoadGameInstance)
		{
			return 0.f;
		}
		else
		{
			return LoadGameInstance->FirstScore;	
		}
	}

	return 0.f;
}