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

	SpawnCooldown = 1.f;

	LineNumMax = 7;
	// 장애물의 개수는 2 ~ 6
	ObstacleMin = 2;
	ObstacleMax = 6;

	SpawnObstacleNumber = 0;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;

	DeactivateVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("DeactivateVolume"));
	DeactivateVolume->SetupAttachment(RootComponent);
	DeactivateVolume->SetRelativeScale3D(FVector(0.5f,0.5f,0.5f));
	DeactivateVolume->OnComponentBeginOverlap.AddDynamic(this, &AObstacleSpawner::OnOverlapBegin);
	//DeactivateVolume->SetRelativeLocation(FVector(SpawnVolume->Bounds.BoxExtent.X, -SpawnVolume->Bounds.BoxExtent.Y, 20.f));

	ObjectPooler = CreateDefaultSubobject<UObjectPoolerComponent>(TEXT("ObjectPooler"));
	PlayScore = 0.f;
}

void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AObstacleSpawner::Spawn, SpawnCooldown, false);
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

void AObstacleSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto ObstacleActor = Cast<AObstacle>(OtherActor);
	if (ObstacleActor != nullptr)
	{
		// 여러 개의 장애물 중 해당 태그가 달린 오브젝트와 만날 때에만 Score를 갱신
		if (ObstacleActor->ActorHasTag("Score Calculate Obstacle"))
		{
			PlayScore += 0.25f;
			UE_LOG(LogTemp, Warning, TEXT("Play Score : %f"), PlayScore);
		}
		ObstacleActor->Deactivate();
	}
}

void AObstacleSpawner::Spawn()
{
	ChooseSpawnLine();


	for (int i = 0; i < SpawnObstacleNumber; i++)
	{
		AObstacle* ObstacleActor = ObjectPooler->GetPooledObject();

		// Obstacle 클래스가 null 이면 오류 띄우고 return
		if (ObstacleActor == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn - object pool drained. Retrying in %f seconds."), SpawnCooldown);
			GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AObstacleSpawner::Spawn, SpawnCooldown, false);
			return;
		}
		
		// Obstacle 액터 위치 계산 및 보이게 하기
		float Distance = 2 * SpawnVolume->Bounds.BoxExtent.X;
		float ObstacleXLoc = SpawnVolume->Bounds.BoxExtent.X - Distance / LineNumMax * 1/2 - Distance / LineNumMax * SpawnLineNumber[i];
		UE_LOG(LogTemp, Warning, TEXT("Spawn Number : %d."), SpawnLineNumber[i]);

		FVector ActorLocation = FVector(ObstacleXLoc, SpawnVolume->Bounds.BoxExtent.Y, 20.f);
		
		ObstacleActor->SetActorLocation(ActorLocation);
		ObstacleActor->SetActive(true);

		// 여러 개의 장애물 중 한 개는 Score를 계산할 수 있음을 나타내는 태그를 달아줌.
		if (i == 0)
		{
			ObstacleActor->Tags.Add("Score Calculate Obstacle");
		}
	}
	SpawnLineNumber.Empty();


	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AObstacleSpawner::Spawn, SpawnCooldown, false);
}

