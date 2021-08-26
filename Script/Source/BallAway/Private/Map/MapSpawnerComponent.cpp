
#include "Map/MapSpawnerComponent.h"
#include "Map/MapActor.h"

UMapSpawnerComponent::UMapSpawnerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SpawnSize = 10;
}

void UMapSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (nullptr != LeftMap1 && nullptr != LeftMap2)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			for (int i = 0; i < SpawnSize; i++)
			{
				AMapActor* Left_Map1 = World->SpawnActor<AMapActor>(LeftMap1, FVector(0.f, 0.f, -1500.f), FRotator().ZeroRotator);
				Left_Map1->SetActive(false);
				//Left_Map1->SetDescentSpeed(DescentSpeed);
				LeftMaps.Add(Left_Map1);

				AMapActor* Left_Map2 = World->SpawnActor<AMapActor>(LeftMap2, FVector(0.f, 0.f, -1500.f), FRotator().ZeroRotator);
				Left_Map2->SetActive(false);
				LeftMaps.Add(Left_Map1);
			}
		}
	}

	if (nullptr != RightMap1 && nullptr != RightMap2)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			for (int i = 0; i < SpawnSize; i++)
			{
				AMapActor* Right_Map1 = World->SpawnActor<AMapActor>(RightMap1, FVector(0.f, 0.f, -1500.f), FRotator().ZeroRotator);
				Right_Map1->SetActive(false);
				//Left_Map1->SetDescentSpeed(DescentSpeed);
				RightMaps.Add(Right_Map1);

				AMapActor* Right_Map2 = World->SpawnActor<AMapActor>(RightMap2, FVector(0.f, 0.f, -1500.f), FRotator().ZeroRotator);
				Right_Map2->SetActive(false);
				RightMaps.Add(Right_Map2);
			}
		}
	}
	
}

AMapActor* UMapSpawnerComponent::GetLeftMaps()
{
	for (AMapActor* LeftMap : LeftMaps)
	{
		if (!LeftMap->IsActive())
		{
			return LeftMap;
		}
	}
	return nullptr;
}

AMapActor* UMapSpawnerComponent::GetRightMaps()
{
	for (AMapActor* RightMap : RightMaps)
	{
		if (!RightMap->IsActive())
		{
			return RightMap;
		}
	}
	return nullptr;
}

void UMapSpawnerComponent::SetDescentSpeed(float DescentSpeed)
{
	for (AMapActor* LeftMap : LeftMaps)
	{
		LeftMap->SetDescentSpeed(DescentSpeed);
	}

	for (AMapActor* RightMap : RightMaps)
	{
		RightMap->SetDescentSpeed(DescentSpeed);
	}
}

