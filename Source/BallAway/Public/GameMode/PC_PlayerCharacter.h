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
	virtual void SetupInputComponent() override;

	// Touch
	void OnTouchBegin(ETouchIndex::Type TouchIndex, FVector TouchLocation);
	void OnTouchTick(ETouchIndex::Type TouchIndex, FVector TouchLocation);
	void OnTouchEnd(ETouchIndex::Type TouchIndex, FVector TouchLocation);

private : 
	FVector FirstLocation;
	FVector CurrentLocation;
	FVector PrevLocation;

	FVector DesiredLocation;

	FVector MoveDirection;

	float DistanceToPlayer;
	float DistanceFromTouch;

	class APlayerCharacter* BAPlayer;
};
