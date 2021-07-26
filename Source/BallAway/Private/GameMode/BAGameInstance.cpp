// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BAGameInstance.h"

UBAGameInstance::UBAGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable>
	DT_Obstacle_SizeProb (TEXT("/Game/GameData/DT_Obstacle_SizeProb.DT_Obstacle_SizeProb"));
	if (DT_Obstacle_SizeProb.Succeeded())
	{
		ObstacleSizeProbTable = DT_Obstacle_SizeProb.Object;
	}
	BACHECK(ObstacleSizeProbTable->GetRowMap().Num() > 0);
}

void UBAGameInstance::Init()
{
	Super::Init();
	//BALOG(Warning,TEXT("Prob Size 2 Phase 1 : %d"),GetObstacleSizeProb(2)->GetPhase(EPhase::Phase1));
}

int32 UBAGameInstance::GetObstacleSizeProb(int32 Size, EPhase CurrentPhase)
{
	int32 Cumulate = 0;

	for (int i = Size; i > 1; i--)
	{
		Cumulate += ObstacleSizeProbTable->FindRow<FObstacleSizeProb>(*FString::FromInt(i), TEXT(""))->GetPhase(CurrentPhase);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, FString::Printf(TEXT("Cumulate :  %d"), Cumulate));

	return Cumulate;
}
