// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GM_InGame.h"
#include "PlayerCharacter/PC_PlayerCharacter.h"
#include "PlayerCharacter/PlayerCharacter.h"
#include "UI/BAHUD.h"

#include "BallAway/Public/GameMode/BASaveGame.h"
#include "Kismet/GameplayStatics.h"

AGM_InGame::AGM_InGame()
{
	PlayScore = 0.f;

	// Player Character
	static ConstructorHelpers::FClassFinder<ACharacter>
	PlayerCharacter(TEXT("/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C"));

	DefaultPawnClass = PlayerCharacter.Class;

	// Player Controller
	PlayerControllerClass = APC_PlayerCharacter::StaticClass();

	// HUD
	static ConstructorHelpers::FClassFinder<ABAHUD>
	HudClass(TEXT("/Game/UI/BP_BAHUD.BP_BAHUD_C"));

	HUDClass = HudClass.Class;

	BestScore = LoadScore();
}

void AGM_InGame::Save()
{
	UBASaveGame* SaveGameInstance = Cast<UBASaveGame>(UGameplayStatics::CreateSaveGameObject(UBASaveGame::StaticClass()));

	if (SaveGameInstance)
	{
		// file data
		SaveGameInstance->SaveSlotName = "SaveGame";
		SaveGameInstance->SaveIndex = 0;

		// TODO : BestScore만 저장하기
		if (BestScore < PlayScore)
		{
			SaveGameInstance->FirstScore = PlayScore;
		}
		else
		{
			SaveGameInstance->FirstScore = BestScore;
		}
	}
	else
	{
		BALOG(Warning, TEXT("SaveGameInstance is nullptr"));
	}

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->SaveIndex);
}

float AGM_InGame::LoadScore()
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