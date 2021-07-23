// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "GameFramework/PlayerController.h"
#include "PC_PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class BALLAWAY_API APC_PlayerCharacter : public APlayerController
{
	GENERATED_BODY()

protected : 
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	// Touch
	void OnTouchBegin(ETouchIndex::Type TouchIndex, FVector TouchLocation);
	void OnTouchTick(ETouchIndex::Type TouchIndex, FVector TouchLocation);
	void OnTouchEnd(ETouchIndex::Type TouchIndex, FVector TouchLocation);

private : 

	class APlayerCharacter* BAPlayer;

	FVector2D CurrentLocation;

	FVector2D MoveDirection;
	FVector2D PlayerScreenLocation;

	bool IsPlayerSpawned;

};
