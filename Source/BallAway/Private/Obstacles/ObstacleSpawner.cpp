// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/ObstacleSpawner.h"

#include "ObjectPoolerComponent.h"
#include "Obstacle.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

AObstacleSpawner::AObstacleSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnCooldown = 3.f;

	LineNumMax = 7;
	// 장애물의 개수는 2 ~ 6
	ObstacleMin = 2;
	ObstacleMax = 6;

	SpawnObstacleNumber = 0;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;

	ObjectPooler = CreateDefaultSubobject<UObjectPoolerComponent>(TEXT("ObjectPooler"));

}

void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AObstacleSpawner::Spawn, SpawnCooldown, false);
}


float AObstacleSpawner::GetLifespanVal()
{
	return 5.0f;
}


void AObstacleSpawner::ChooseSpawnLine()
{
	// 1. 생성할 오브젝트의 개수를 정함
	SpawnObstacleNumber = FMath::RandRange(ObstacleMin, ObstacleMax);

	UE_LOG(LogTemp, Warning, TEXT("Obstacle Number : %d."), SpawnObstacleNumber);

	// 2. 오브젝트를 생성할 라인을 정해 배열에 저장
	for (int i = 0; i < SpawnObstacleNumber; i++)
	{
		while (true)
		{
			int32 SpawnLine = FMath::RandRange(0, LineNumMax - 1);
			if (SpawnLineNumber.Contains(SpawnLine))
			{
				continue;
			}
			else
			{
				SpawnLineNumber.Emplace(SpawnLine);
				break;
			}
		}

	}
	
}

void AObstacleSpawner::Spawn()
{
	ChooseSpawnLine();

	for (int i = 0; i < SpawnObstacleNumber; i++)
	{
		AObstacle* PoolableActor = ObjectPooler->GetPooledObject();

		if (PoolableActor == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn - object pool drained. Retrying in %f seconds."), SpawnCooldown);
			GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AObstacleSpawner::Spawn, SpawnCooldown, false);
			return;
		}
		
		float Distance = 2 * SpawnVolume->Bounds.BoxExtent.X;
		float ObstacleXLoc = SpawnVolume->Bounds.BoxExtent.X - Distance / LineNumMax * 1/2 - Distance / LineNumMax * SpawnLineNumber[i];
		UE_LOG(LogTemp, Warning, TEXT("Spawn Number : %d."), SpawnLineNumber[i]);

		FVector ActorLocation = FVector(ObstacleXLoc, SpawnVolume->Bounds.BoxExtent.Y, 20.f);

		PoolableActor->SetActorLocation(ActorLocation);
		PoolableActor->SetLifeSpan(GetLifespanVal());
		PoolableActor->SetActive(true);
	}
	SpawnLineNumber.Empty();


	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AObstacleSpawner::Spawn, SpawnCooldown, false);
}

