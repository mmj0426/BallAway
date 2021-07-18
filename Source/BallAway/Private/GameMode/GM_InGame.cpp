// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GM_InGame.h"
#include "GameMode/PC_PlayerCharacter.h"
#include "PlayerCharacter/PlayerCharacter.h"

AGM_InGame::AGM_InGame()
{
	static ConstructorHelpers::FClassFinder<ACharacter>
	PlayerCharacter(TEXT("/Game/Blueprints/BP_PlayerCharacter.BP_PlayerCharacter_C"));

	DefaultPawnClass = PlayerCharacter.Class;

	PlayerControllerClass = APC_PlayerCharacter::StaticClass();
}