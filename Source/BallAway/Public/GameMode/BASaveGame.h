// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "GameFramework/SaveGame.h"
#include "BASaveGame.generated.h"

/**
 * 
 */
UCLASS()
class BALLAWAY_API UBASaveGame : public USaveGame
{
	GENERATED_BODY()
	
public : 
	// Save game data file name
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	FString SaveSlotName;		

	// Save game data file index
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	int32 SaveIndex;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "SaveData")
	float SaveScore;
};
