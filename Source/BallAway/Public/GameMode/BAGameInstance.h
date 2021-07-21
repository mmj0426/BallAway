// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"

#include "ObstacleSpawner.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "BAGameInstance.generated.h"

USTRUCT(BlueprintType)
struct FObstacleSizeProb : public FTableRowBase
{
	GENERATED_BODY()

public : 
	FObstacleSizeProb() : Phase1(0.f),Phase2(0.f),Phase3(0.f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Phase1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Phase2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int32 Phase3;

	int32 GetPhase(EPhase CurrentPhase)
	{
		switch (CurrentPhase)
		{
		case EPhase::Phase1:
			return Phase1;

		case EPhase::Phase2:
			return Phase2;

		case EPhase::Phase3:
			return Phase3;

		default:
			return 0;
		}
		return 0;
	}
};

UCLASS()
class BALLAWAY_API UBAGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public : 
	UBAGameInstance();
	virtual void Init() override;

	FObstacleSizeProb* GetObstacleSizeProb(int32 Size);

	
private :
	UPROPERTY()
	class UDataTable* ObstacleSizeProbTable;
};
