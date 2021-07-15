// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/ObstacleSpawner.h"

#include "ObjectPoolerComponent.h"
#include "Obstacle.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

AObstacleSpawner::AObstacleSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnCooldown = 3.f;
	SparkingMode = false;
	SparklesVelocity = 100.f;

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

	return UKismetMathLibrary::RandomPointInBoundingBox(SpawnOrigin, SpawnExtent);
}

float AObstacleSpawner::GetLifespanVal()
{
	return 5.0f;
}

void AObstacleSpawner::Spawn()
{
	AObstacle* PoolableActor = ObjectPooler->GetPooledObject();

	if (PoolableActor == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot spawn - object pool drained. Retrying in %f seconds."), SpawnCooldown);
		GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AObstacleSpawner::Spawn, SpawnCooldown, false);
		return;
	}

	FVector ActorLocation;
	float SparklesVelocityTmp;
	FVector SparklesDirectionTmp;

	/* if sparkling mode is enabled all objects would spawn from the center of the spawner and will have a velocity outwards*/
	if (SparkingMode)
	{
		ActorLocation = SpawnVolume->Bounds.Origin;
		SparklesVelocityTmp = SparklesVelocity;
		SparklesDirectionTmp = UKismetMathLibrary::RandomUnitVector();
	}
	/* otherwise objects should spawn randomly within the spawn box extents */
	else
	{
		ActorLocation = GetRandomPointInVolume();
		SparklesVelocityTmp = 0.f;
		SparklesDirectionTmp = FVector().ZeroVector;
	}

	PoolableActor->SetActorLocation(ActorLocation);
	//UE_LOG(LogTemp, Warning, TEXT("Location : %f %f %f"), ActorLocation.X, ActorLocation.Y, ActorLocation.Z);
	PoolableActor->SetLifeSpan(GetLifespanVal());
	PoolableActor->SetActive(true);
	//PoolableActor->SetVelocity(SparklesVelocity);
	//PoolableActor->SetDirection(SparklesDirectionTmp);

	/* setup next spawn call within a given cooldown */
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AObstacleSpawner::Spawn, SpawnCooldown, false);
}

