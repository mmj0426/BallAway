// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/ObstacleSpawner.h"

#include "ObjectPoolerComponent.h"
#include "Obstacle.h"
#include "BAGameInstance.h"
#include "GM_InGame.h"
//#include "PhaseEnum.h"

#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

AObstacleSpawner::AObstacleSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnCooldown = 1.f;

	LineNumMax = 7;
	// ��ֹ��� ������ 2 ~ 6
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
	CurrentPhase = EPhase::Phase1;
}

void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AObstacleSpawner::Spawn, SpawnCooldown, false);
}

void AObstacleSpawner::DecideObstacleSize()
{
	auto BAGameInstance = Cast<UBAGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	int32 RandomNum = FMath::RandRange(0,99);
	UE_LOG(LogTemp, Warning, TEXT("Random Number : %d."), RandomNum);

	// ����� ���� ��ֹ� ũ�� Ȯ�� ����
	if (RandomNum >= 0 && RandomNum < BAGameInstance->GetObstacleSizeProb(2,CurrentPhase))
	{
		SpawnObstacleNumber = 2;
	}
	else if (RandomNum >= BAGameInstance->GetObstacleSizeProb(2, CurrentPhase)
		&& RandomNum < BAGameInstance->GetObstacleSizeProb(3, CurrentPhase))
	{
		SpawnObstacleNumber = 3;
	}
	else if (RandomNum >= BAGameInstance->GetObstacleSizeProb(3, CurrentPhase)
		&& RandomNum < BAGameInstance->GetObstacleSizeProb(4, CurrentPhase))
	{
		SpawnObstacleNumber = 4;
	}
	else if (RandomNum >= BAGameInstance->GetObstacleSizeProb(4, CurrentPhase)
		&& RandomNum < BAGameInstance->GetObstacleSizeProb(5, CurrentPhase))
	{
		SpawnObstacleNumber = 5;
	}
	else if (RandomNum >= BAGameInstance->GetObstacleSizeProb(5, CurrentPhase)
		&& RandomNum < BAGameInstance->GetObstacleSizeProb(6, CurrentPhase))
	{
		SpawnObstacleNumber = 6;
	}
	
	UE_LOG(LogTemp, Warning, TEXT("Obstacle Number : %d."), SpawnObstacleNumber);
	return;

}

void AObstacleSpawner::ChooseSpawnLine()
{
	// 1. ������ ������Ʈ�� ������ ����
	DecideObstacleSize();

	// 2. ������Ʈ�� ������ ������ ���� �迭�� ����
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
		// ���� ���� ��ֹ� �� �ش� �±װ� �޸� ������Ʈ�� ���� ������ Score�� ����
		if (ObstacleActor->ActorHasTag("Score Calculate Obstacle"))
		{
			auto GameMode = Cast<AGM_InGame>(GetWorld()->GetAuthGameMode());

			GameMode->PlayScore += 0.25f;

			// 1���� ���� ������ �ӷ� ����
			if (FMath::Fmod(GameMode->PlayScore, 1) == 0.f)
			{
				// TODO : �ӷ� ����
				ObjectPooler->DescentSpeedReduction();

				// ��ֹ��� �ӵ��� �������� ��Ÿ�ӵ� ���� �������� ��.
				SpawnCooldown += ObjectPooler->GetSpeedReductionRate();
			}

			// ���ھ� ���� �� ���ؼ� ������ ����
			if (GameMode->PlayScore == 40.25)
			{
				CurrentPhase = EPhase::Phase2;
			}
			if (GameMode->PlayScore == 90.25)
			{
				CurrentPhase = EPhase::Phase3;
			}


			UE_LOG(LogTemp, Warning, TEXT("Play Score : %f"), GameMode->PlayScore);
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

		// Obstacle Ŭ������ null �̸� ���� ���� return
		if (ObstacleActor == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn - object pool drained. Retrying in %f seconds."), SpawnCooldown);
			GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AObstacleSpawner::Spawn, SpawnCooldown, false);
			return;
		}
		
		// Obstacle ���� ��ġ ��� �� ���̰� �ϱ�
		float Distance = 2 * SpawnVolume->Bounds.BoxExtent.X;
		float ObstacleXLoc = SpawnVolume->Bounds.BoxExtent.X - Distance / LineNumMax * 1/2 - Distance / LineNumMax * SpawnLineNumber[i];
		//UE_LOG(LogTemp, Warning, TEXT("Spawn Number : %d."), SpawnLineNumber[i]);

		FVector ActorLocation = FVector(ObstacleXLoc, SpawnVolume->Bounds.BoxExtent.Y, 20.f);
		
		ObstacleActor->SetActorLocation(ActorLocation);
		ObstacleActor->SetActive(true);

		// ���� ���� ��ֹ� �� �� ���� Score�� ����� �� ������ ��Ÿ���� �±׸� �޾���.
		if (i == 0)
		{
			ObstacleActor->Tags.Add("Score Calculate Obstacle");
		}
	}
	SpawnLineNumber.Empty();


	GetWorldTimerManager().SetTimer(SpawnCooldownTimer, this, &AObstacleSpawner::Spawn, SpawnCooldown, false);
}

