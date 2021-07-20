// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
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
	float Phase1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Phase2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	float Phase3;
};

UCLASS()
class BALLAWAY_API UBAGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public : 
	UBAGameInstance();
	virtual void Init() override;

	FObstacleSizeProb* GetObstacleSizeProb(int Size);
	
private :
	UPROPERTY()
	class UDataTable* ObstacleSizeProbTable;
};
