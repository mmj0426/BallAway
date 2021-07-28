// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"

#include "PhaseEnum.h"
#include "Engine/DataTable.h"
#include "Engine/GameInstance.h"
#include "BAGameInstance.generated.h"


UCLASS()
class BALLAWAY_API UBAGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UBAGameInstance();
	virtual void Init() override;

	int32 GetObstacleSizeProb(int32 Size, EPhase CurrentPhase);
	int32 GetItemSpawnProb(FName ItemName, EPhase CurrentPhase);


private:
	UPROPERTY()
	class UDataTable* ObstacleSizeProbTable;

	UPROPERTY()
	class UDataTable* ItemSpawnProbTable;
};


USTRUCT(BlueprintType)
struct FProbDataStruct : public FTableRowBase
{
	GENERATED_BODY()

public : 
	FProbDataStruct() : Phase1(0.f),Phase2(0.f),Phase3(0.f) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObstacleData")
	int32 Phase1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObstacleData")
	int32 Phase2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ObstacleData")
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

//USTRUCT(BlueprintType)
//struct FItemSpawnProb : public FTableRowBase
//{
//public:
//	FItemSpawnProb() : Phase1(0.f), Phase2(0.f), Phase3(0.f) {}
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
//	int32 Phase1;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
//	int32 Phase2;
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ItemData")
//	int32 Phase3;
//
//
//	int32 GetPhase(EPhase CurrentPhase)
//	{
//		switch (CurrentPhase)
//		{
//		case EPhase::Phase1:
//			return Phase1;
//
//		case EPhase::Phase2:
//			return Phase2;
//
//		case EPhase::Phase3:
//			return Phase3;
//
//		default:
//			return 0;
//		}
//		return 0;
//	}
//
//};