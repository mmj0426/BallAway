#pragma once

#include "../BallAway.h"
#include "GameFramework/PlayerController.h"
#include "PC_PlayerCharacter.generated.h"

DECLARE_MULTICAST_DELEGATE(FPlayerSpawned);

UCLASS()
class BALLAWAY_API APC_PlayerCharacter : public APlayerController
{
	GENERATED_BODY()

public : 
	FPlayerSpawned OnPlayerSpawned;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

protected:

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
