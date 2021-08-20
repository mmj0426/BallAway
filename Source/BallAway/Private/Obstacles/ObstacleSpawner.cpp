// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/ObstacleSpawner.h"

#include "PlayerCharacter/PC_PlayerCharacter.h"
#include "ObjectPoolerComponent.h"
#include "Obstacle.h"
#include "BAGameInstance.h"
#include "GM_InGame.h"
#include "Item/SpeedUpItem.h"
#include "UI/BAHUD.h"
#include "UI/InGameWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

AObstacleSpawner::AObstacleSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	LineNumMax = 7;

	// ��ֹ��� ������ 2 ~ 6
	ObstacleMin = 2;
	ObstacleMax = 6;

	SpawnObstacleNumber = 0;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;

	DeactivateVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("DeactivateVolume"));
	DeactivateVolume->SetupAttachment(RootComponent);
<<<<<<< HEAD
	DeactivateVolume->SetRelativeScale3D(FVector(0.5f,0.5f,0.5f));
	DeactivateVolume->OnComponentBeginOverlap.AddDynamic(this, &AObstacleSpawner::OnOverlapBegin);
	//DeactivateVolume->SetRelativeLocation(FVector(SpawnVolume->Bounds.BoxExtent.X, -SpawnVolume->Bounds.BoxExtent.Y, 20.f));
=======
	DeactivateVolume->SetRelativeScale3D(FVector(0.5f));

	PauseVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("PauseVolume"));
	PauseVolume->SetupAttachment(RootComponent);
	IsFirstOverlap = true;
>>>>>>> feacher/Obstacles

	ObjectPooler = CreateDefaultSubobject<UObjectPoolerComponent>(TEXT("ObjectPooler"));

	CurrentPhase = EPhase::Phase1;

	// ������ ���� �ʱ�ȭ
	ItemSpawnCooldown = 10.f;
	CanItemSpawn = false;

}

void AObstacleSpawner::BeginPlay()
{
	Super::BeginPlay();
<<<<<<< HEAD
=======

	ObjectPooler->SetAnimalObstacleMesh(CurrentPhase);

	DeactivateVolume->OnComponentBeginOverlap.AddDynamic(this, &AObstacleSpawner::DeactivateOverlapBegin);
	PauseVolume->OnComponentBeginOverlap.AddDynamic(this, &AObstacleSpawner::PauseOverlapBegin);
>>>>>>> feacher/Obstacles
	
	Spawn();

	auto PlayerController = Cast<APC_PlayerCharacter>(UGameplayStatics::GetPlayerController(GetWorld(),0));


	if (PlayerController)
	{
		PlayerController->CanPlayerSpawn = false;

		PlayerController->OnPlayerSpawned.AddLambda([this]()->void
		{
			ObjectPooler->SetSpeed(ObjectPooler->GetDescentSpeed());
			BALOG(Error, TEXT("Descent Speed : %f "), ObjectPooler->GetDescentSpeed());
			GetWorldTimerManager().SetTimer(ItemSpawnCooldownTimer, this, &AObstacleSpawner::SetCanItemSpawn, ItemSpawnCooldown, true);
			GetWorldTimerManager().SetTimer(ObstacleSpawnCooldownTimer, this, &AObstacleSpawner::Spawn, ObjectPooler->ObstacleSpawnCooldown, false);
				
		});
	}

}

void AObstacleSpawner::DecideObstacleSize()
{
	auto BAGameInstance = Cast<UBAGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	int32 RandomNum = FMath::RandRange(0,99);
	//UE_LOG(LogTemp, Warning, TEXT("Random Number : %d."), RandomNum);

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
	
	//UE_LOG(LogTemp, Warning, TEXT("Obstacle Number : %d."), SpawnObstacleNumber);
	return;

}

void AObstacleSpawner::ChooseSpawnLine()
{
	// 1. ������ ������Ʈ�� ������ ����
	DecideObstacleSize();

	// 2. ������Ʈ�� ������ ������ ���� �迭�� ����

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

void AObstacleSpawner::DeactivateOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto ObstacleActor = Cast<AObstacle>(OtherActor);

	if (nullptr != ObstacleActor)
	{
		// ���� ���� ��ֹ� �� �ش� �±װ� �޸� ������Ʈ�� ���� ������ Score�� ����
		if (ObstacleActor->ActorHasTag("Score Calculate Obstacle"))
		{
			auto GameMode = Cast<AGM_InGame>(GetWorld()->GetAuthGameMode());

			GameMode->PlayScore += 0.25f;

			// UI : HUD�����ͼ� Score���� ����
			auto ScoreWidget = Cast<ABAHUD>(UGameplayStatics::GetPlayerController(GetWorld(),0)->GetHUD())->GetInGameWidget();
			
			ScoreWidget->SetPlayScoreText(GameMode->PlayScore);

			// 1���� ���� ������ �ӷ� ����
			if (FMath::Fmod(GameMode->PlayScore, 1) == 0.f)
			{
				ObjectPooler->DescentSpeedDecrease();
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
		}

		ObstacleActor->Deactivate();
	}

}

void AObstacleSpawner::PauseOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto FirstOverlapActor = Cast<AAnimalObstacles>(OtherActor);

	if (nullptr != FirstOverlapActor && IsFirstOverlap)
	{
		if (FirstOverlapActor->ActorHasTag("Score Calculate Obstacle"))
		{
			//UGameplayStatics::SetGamePaused(GetWorld(), true);
			ObjectPooler->SetSpeed(0.f);
			IsFirstOverlap = false;

			auto PlayerController = Cast<APC_PlayerCharacter>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

			if (PlayerController)
			{
				PlayerController->CanPlayerSpawn = true;
			}
		}
	}

}

void AObstacleSpawner::SetCanItemSpawn()
{

	// ������ ���� Ȯ�� ����
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
	// ��ֹ� ����
	ChooseSpawnLine();

	for (int i = 0; i < SpawnLineNumber.Num(); i++)
	{
		AObstacle* ObstacleActor = ObjectPooler->GetPooledObstacle();

		// Obstacle Ŭ������ null �̸� ���� ���� return
		if (nullptr == ObstacleActor)
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot spawn - object pool drained. Retrying in %f seconds."), ObjectPooler->ObstacleSpawnCooldown);
			GetWorldTimerManager().SetTimer(ObstacleSpawnCooldownTimer, this, &AObstacleSpawner::Spawn, ObjectPooler->ObstacleSpawnCooldown, false);
			return;
		}
		
		// Obstacle ���� ��ġ ��� �� ���̰� �ϱ�
		float Distance = 2 * SpawnVolume->Bounds.BoxExtent.X;
		float ObstacleXLoc = SpawnVolume->Bounds.BoxExtent.X - Distance / LineNumMax * 1/2 - Distance / LineNumMax * SpawnLineNumber[i];
		//UE_LOG(LogTemp, Warning, TEXT("Spawn Number : %d."), SpawnLineNumber[i]);

		FVector ActorLocation = FVector(ObstacleXLoc, SpawnVolume->Bounds.BoxExtent.Y, 90.f);
		
		ObstacleActor->SetActorLocation(ActorLocation);
		ObstacleActor->SetActive(true);

		// ���� ���� ��ֹ� �� �� ���� Score�� ����� �� ������ ��Ÿ���� �±׸� �޾���.
		if (i == 0)
		{
			ObstacleActor->Tags.Add("Score Calculate Obstacle");
		}
	}
	SpawnLineNumber.Empty();

	if (CanItemSpawn)
	{
		// ������ ����
		float Distance = 2 * SpawnVolume->Bounds.BoxExtent.X;
		float ItemXLoc = SpawnVolume->Bounds.BoxExtent.X - Distance / LineNumMax * 1 / 2 - Distance / LineNumMax * ItemSpawnLine;
		FVector SpawnLocation = FVector(ItemXLoc, SpawnVolume->Bounds.BoxExtent.Y, 90.f);

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

	BALOG(Warning, TEXT("Obstacle Spawn Cooldown : %f"), ObjectPooler->ObstacleSpawnCooldown);
	if (!IsFirstOverlap)
	{
		GetWorldTimerManager().SetTimer(ObstacleSpawnCooldownTimer, this, &AObstacleSpawner::Spawn, ObjectPooler->ObstacleSpawnCooldown, false);
	}
}


