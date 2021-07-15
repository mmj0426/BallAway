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
	//SparkingMode = false;
	//SparklesVelocity = 100.f;
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

FVector AObstacleSpawner::GetRandomPointInVolume()
{
	FVector SpawnOrigin = SpawnVolume->Bounds.Origin;
	FVector SpawnExtent = SpawnVolume->Bounds.BoxExtent;
	UE_LOG(LogTemp, Warning, TEXT("SpawnVolume Extent : %f, %f, %f"), SpawnExtent.X, SpawnExtent.Y, SpawnExtent.Z);

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

float AObstacleSpawner::GetLifespanVal()
{
	return 5.0f;
}

void AObstacleSpawner::SetSpawnObstacleNumber()
{
	SpawnObstacleNumber = FMath::RandRange(ObstacleMin,ObstacleMax);
	UE_LOG(LogTemp, Warning, TEXT("Random Number : %d"), SpawnObstacleNumber);
}

void AObstacleSpawner::Spawn()
{
	SetSpawnObstacleNumber();

	for (int i = 0; i < SpawnObstacleNumber; i++)
	{
		AObstacle* PoolableActor = ObjectPooler->GetPooledObject();

		if (PoolableActor == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn - object pool drained. Retrying in %f seconds."), SpawnCooldown);
			GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AObstacleSpawner::Spawn, SpawnCooldown, false);
			return;
		}

		FVector ActorLocation = FVector(GetRandomPointInVolume().X, SpawnVolume->Bounds.BoxExtent.Y, 20.f);
		//ActorLocation = GetRandomPointInVolume();

		PoolableActor->SetActorLocation(ActorLocation);
		PoolableActor->SetLifeSpan(GetLifespanVal());
		PoolableActor->SetActive(true);
	}


	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AObstacleSpawner::Spawn, SpawnCooldown, false);
}

