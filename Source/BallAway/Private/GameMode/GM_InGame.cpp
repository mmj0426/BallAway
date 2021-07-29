// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GM_InGame.h"
#include "PlayerCharacter/PC_PlayerCharacter.h"
#include "PlayerCharacter/PlayerCharacter.h"

#include "BallAway/Public/GameMode/BASaveGame.h"
#include "Kismet/GameplayStatics.h"

AGM_InGame::AGM_InGame()
{
	PlayScore = 0.f;

	static ConstructorHelpers::FClassFinder<ACharacter>
	PlayerCharacter(TEXT("/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C"));

	DefaultPawnClass = PlayerCharacter.Class;

	PlayerControllerClass = APC_PlayerCharacter::StaticClass();

	Load();
}

void AGM_InGame::Save()
{
	UBASaveGame* SaveGameInstance = Cast<UBASaveGame>(UGameplayStatics::CreateSaveGameObject(UBASaveGame::StaticClass()));

	if (SaveGameInstance)
	{
		// file data
		SaveGameInstance->SaveSlotName = "SaveGame";
		SaveGameInstance->SaveIndex = 0;

		// TODO : 게임오버 조건 만들어지면 score 저장하기
		SaveGameInstance->SaveScore = PlayScore;
	}
	else
	{
		BALOG(Warning, TEXT("SaveGameInstance is nullptr"));
	}

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, SaveGameInstance->SaveIndex);
}

void AGM_InGame::Load()
{
	UBASaveGame* LoadGameInstance = Cast<UBASaveGame>(UGameplayStatics::CreateSaveGameObject(UBASaveGame::StaticClass()));

	if (LoadGameInstance)
	{
		LoadGameInstance->SaveSlotName = "SaveGame";
		LoadGameInstance->SaveIndex = 0;

		LoadGameInstance = Cast<UBASaveGame>(UGameplayStatics::LoadGameFromSlot(LoadGameInstance->SaveSlotName, LoadGameInstance->SaveIndex));

		BALOG(Warning, TEXT("Save Score : %f"), LoadGameInstance->SaveScore);
	}
}