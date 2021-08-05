// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/ObstacleSpawner.h"

#include "ObjectPoolerComponent.h"
#include "Obstacle.h"
#include "Obstacles/AnimalObstacles.h"
#include "BAGameInstance.h"
#include "GM_InGame.h"
#include "Item/SpeedUpItem.h"
#include "UI/BAHUD.h"
#include "UI/ScoreWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

AObstacleSpawner::AObstacleSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	LineNumMax = 7;

	// 장애물의 개수는 2 ~ 6
	ObstacleMin = 2;
	ObstacleMax = 6;

	SpawnObstacleNumber = 0;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;

	DeactivateVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("DeactivateVolume"));
	DeactivateVolume->SetupAttachment(RootComponent);
	DeactivateVolume->SetRelativeScale3D(FVector(0.5f));
	DeactivateVolume->OnComponentBeginOverlap.AddDynamic(this, &AObstacleSpawner::OnOverlapBegin);
	//DeactivateVolume->SetRelativeLocation(FVector(SpawnVolume->Bounds.BoxExtent.X, -SpawnVolume->Bounds.BoxExtent.Y, 20.f));

	ObjectPooler = CreateDefaultSubobject<UObjectPoolerComponent>(TEXT("ObjectPooler"));

	CurrentPhase = EPhase::Phase1;

	// 아이템 변수 초기화
	ItemSpawnCooldown = 10.f;
	CanItemSpawn = false;

}

void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();

	ObjectPooler->SetAnimalObstacleMesh(CurrentPhase);
	
	GetWorldTimerManager().SetTimer(ObstacleSpawnCooldownTimer, this, &AObstacleSpawner::Spawn, ObjectPooler->ObstacleSpawnCooldown, false);
	GetWorldTimerManager().SetTimer(ItemSpawnCooldownTimer, this,&AObstacleSpawner::SetCanItemSpawn, ItemSpawnCooldown, true);
}

void AObstacleSpawner::DecideObstacleSize()
{
	auto BAGameInstance = Cast<UBAGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	int32 RandomNum = FMath::RandRange(0,99);
	//UE_LOG(LogTemp, Warning, TEXT("Random Number : %d."), RandomNum);

	// 페이즈에 따른 장애물 크기 확률 적용
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
	
	//UE_LOG(LogTemp, Warning, TEXT("Obstacle Number : %d."), SpawnObstacleNumber);
	return;

}

void AObstacleSpawner::ChooseSpawnLine()
{
	// 1. 생성할 오브젝트의 개수를 정함
	DecideObstacleSize();

	// 2. 오브젝트를 생성할 라인을 정해 배열에 저장

	if (CanItemSpawn)
	{
		SpawnObstacleNumber += 1;
	}

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

	if (CanItemSpawn)
	{
		int32 RandomIndex = FMath::RandRange(0, SpawnLineNumber.Num()-1);
		ItemSpawnLine = SpawnLineNumber[RandomIndex];

		BALOG(Error, TEXT("Item Spawn Line : %d"), ItemSpawnLine);

		SpawnLineNumber.RemoveAt(RandomIndex);		
	}

	
}

void AObstacleSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto ObstacleActor = Cast<AAnimalObstacles>(OtherActor);

	if (nullptr != ObstacleActor)
	{
		// 여러 개의 장애물 중 해당 태그가 달린 오브젝트와 만날 때에만 Score를 갱신
		if (ObstacleActor->ActorHasTag("Score Calculate Obstacle"))
		{
			auto GameMode = Cast<AGM_InGame>(GetWorld()->GetAuthGameMode());

			GameMode->PlayScore += 0.25f;

			// UI : HUD가져와서 Score변수 갱신
			auto ScoreWidget = Cast<ABAHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD())->GetPlayScoreWidget();
			
			ScoreWidget->SetPlayScoreText(GameMode->PlayScore);

			// 1점을 얻을 때마다 속력 감소
			if (FMath::Fmod(GameMode->PlayScore, 1) == 0.f)
			{
				ObjectPooler->DescentSpeedDecrease();

				// 장애물의 속도가 느려지면 쿨타임도 같이 느려져야 함.
				ObjectPooler->ObstacleSpawnCooldown += ObjectPooler->GetSpeedReductionRate();
			}

			// 스코어 갱신 후 비교해서 페이즈 갱신
			if (GameMode->PlayScore == 40.25)
			{
				CurrentPhase = EPhase::Phase2;
				ObjectPooler->SetAnimalObstacleMesh(CurrentPhase);
			}
			if (GameMode->PlayScore == 90.25)
			{
				CurrentPhase = EPhase::Phase3;
				ObjectPooler->SetAnimalObstacleMesh(CurrentPhase);
			}
		}
		ObstacleActor->Deactivate();
	}
}

void AObstacleSpawner::SetCanItemSpawn()
{

	// 아이템 스폰 확률 적용
	auto BAGameInstance = Cast<UBAGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	int32 RandomNum = FMath::RandRange(0, 99);

	if (RandomNum >= 0 && RandomNum < BAGameInstance->GetItemSpawnProb(FName(TEXT("SpeedUp")), CurrentPhase))
	{
		CanItemSpawn = true;
	}

	return;
	//CanItemSpawn = true;
}


void AObstacleSpawner::Spawn()
{
	// 장애물 생성
	ChooseSpawnLine();

	for (int i = 0; i < SpawnLineNumber.Num(); i++)
	{
		AAnimalObstacles* ObstacleActor = ObjectPooler->GetPooledObstacle();

		// Obstacle 클래스가 null 이면 오류 띄우고 return
		if (nullptr == ObstacleActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn - object pool drained. Retrying in %f seconds."), ObjectPooler->ObstacleSpawnCooldown);
			GetWorldTimerManager().SetTimer(ObstacleSpawnCooldownTimer, this, &AObstacleSpawner::Spawn, ObjectPooler->ObstacleSpawnCooldown, false);
			return;
		}
		
		// Obstacle 액터 위치 계산 및 보이게 하기
		float Distance = 2 * SpawnVolume->Bounds.BoxExtent.X;
		float ObstacleXLoc = SpawnVolume->Bounds.BoxExtent.X - Distance / LineNumMax * 1/2 - Distance / LineNumMax * SpawnLineNumber[i];
		//UE_LOG(LogTemp, Warning, TEXT("Spawn Number : %d."), SpawnLineNumber[i]);

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

	if (CanItemSpawn)
	{
		// 아이템 생성
		float Distance = 2 * SpawnVolume->Bounds.BoxExtent.X;
		float ItemXLoc = SpawnVolume->Bounds.BoxExtent.X - Distance / LineNumMax * 1 / 2 - Distance / LineNumMax * ItemSpawnLine;
		FVector SpawnLocation = FVector(ItemXLoc, SpawnVolume->Bounds.BoxExtent.Y, 20.f);

		ASpeedUpItem* SpeedUpItemActor = ObjectPooler->GetPooledItem();
		if (nullptr == SpeedUpItemActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn - object pool drained. Retrying in %f seconds."), ObjectPooler->ObstacleSpawnCooldown);
			GetWorldTimerManager().SetTimer(ObstacleSpawnCooldownTimer, this, &AObstacleSpawner::Spawn, ObjectPooler->ObstacleSpawnCooldown, false);
			return;
		}

		SpeedUpItemActor->SetActorLocation(SpawnLocation);
		SpeedUpItemActor->SetActive(true);
		CanItemSpawn = false;
	}


	GetWorldTimerManager().SetTimer(ObstacleSpawnCooldownTimer, this, &AObstacleSpawner::Spawn, ObjectPooler->ObstacleSpawnCooldown, false);
}


