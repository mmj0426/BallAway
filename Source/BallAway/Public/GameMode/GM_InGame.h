// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"

#include "GameFramework/GameModeBase.h"
#include "GM_InGame.generated.h"

/**
 * 
 */
UCLASS()
class BALLAWAY_API AGM_InGame : public AGameModeBase
{
	GENERATED_BODY()
	
public : 
	AGM_InGame();

	void Save();
	void Load();
};
