
#include "Obstacles/ObjectPoolerComponent.h"
#include "Obstacle.h"
#include "Obstacles/AnimalObstacles.h"
#include "Item/SpeedUpItem.h"
#include "Map/MapSpawner.h"
#include "Map/MapSpawnerComponent.h"

#include "Math/UnrealMathUtility.h"
#include "Kismet/GameplayStatics.h"
#include "UI/BAHUD.h"
#include "UI/GameResultWidget.h"
#include "GM_InGame.h"

//#include "Blueprint/WidgetBlueprintLibrary.h"

UObjectPoolerComponent::UObjectPoolerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	PoolSize = 50.f;
	ItemPoolSize = 5.f;

	ObstacleSpawnCooldown = 2.f;

	DescentSpeed = 2.f;
	SpeedDecreaseRate = 0.02f;
	DecreaseCount = 0;
	SpeedIncreaseRate = 0.1f;
}

void UObjectPoolerComponent::BeginPlay()
{
	if (nullptr != ObstacleSubClass)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			// PoolSize��ŭ ������Ʈ ����
			// ������ ������Ʈ�� ��Ȱ���� ���·� Pool�� ��
			for (int i = 0; i < PoolSize; i++)
			{
				AAnimalObstacles* PoolableObstacle = World->SpawnActor<AAnimalObstacles>(ObstacleSubClass, FVector().ZeroVector, FRotator().ZeroRotator);
				PoolableObstacle->SetActive(false);
				PoolableObstacle->SetDescentSpeed(DescentSpeed);
				PoolableObstacle->OnHitPlayer.AddUObject(this, &UObjectPoolerComponent::DescentSpeedDecrease);
				if (i == 0)
				{
					PoolableObstacle->Tags.Add("GameOver Obstacle");
				}
				Pool.Add(PoolableObstacle);
			}
		}
	}

	if (nullptr != ItemSubClass)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			for (int i = 0; i < ItemPoolSize; i++)
			{
				ASpeedUpItem* SpeedUpItem = World->SpawnActor<ASpeedUpItem>(ItemSubClass, FVector().ZeroVector, FRotator().ZeroRotator);
				SpeedUpItem->SetActive(false);
				SpeedUpItem->SetDescentSpeed(DescentSpeed);
				// Speed Up �������� �÷��̾ ���� �� DescentSpeedIncrease �Լ� ȣ��
				SpeedUpItem->OnGetItem.AddUObject(this, &UObjectPoolerComponent::DescentSpeedIncrease);
				Items.Add(SpeedUpItem);
			}
		}
	}

	// Map Speed Synchronize
	TArray<AActor*>MapSpawners;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "MapSpawner", MapSpawners);

	if (MapSpawners.Num() > 0)
	{
		//BALOG(Warning, TEXT("asdf"));
		auto MapSpawner = Cast<AMapSpawner>(MapSpawners[0]);

		MapSpawner->MapComponent->SetDescentSpeed(DescentSpeed);
	}

	Super::BeginPlay();	
}

AAnimalObstacles* UObjectPoolerComponent::GetPooledObstacle()
{
	for (AAnimalObstacles* PoolableObstacle : Pool)
	{
		if (!PoolableObstacle->IsActive())
		{
			return PoolableObstacle;
		}
	}

	return nullptr;
}

ASpeedUpItem* UObjectPoolerComponent::GetPooledItem()
{
	for (ASpeedUpItem* PoolableItem : Items)
	{
		if (!PoolableItem->IsActive())
		{
			return PoolableItem;
		}
	}
	return nullptr;
}

void UObjectPoolerComponent::DescentSpeedDecrease()
{	
	float Speed = 0.f;

	ObstacleSpawnCooldown += SpeedDecreaseRate;
	DecreaseCount++;

	for (AAnimalObstacles* PoolableObstacle : Pool)
	{
		//Speed = FMath::Clamp<float>(PoolableObstacle->GetDescentSpeed() - DescentSpeed * SpeedDecreaseRate * DecreaseCount,0,DescentSpeed);
		Speed = FMath::Clamp<float>(PoolableObstacle->GetDescentSpeed() - PoolableObstacle->GetDescentSpeed() * SpeedDecreaseRate, 0, DescentSpeed);
		PoolableObstacle->SetDescentSpeed(Speed);

		// �ӵ��� 0 ������ �� GameOver UI ���
		if (PoolableObstacle->ActorHasTag("GameOver Obstacle") && PoolableObstacle->GetDescentSpeed() <= 1.f)
		{
			// �Ͻ� ���� �� UI ����
			UGameplayStatics::SetGamePaused(GetWorld(), true);

			auto GameMode = Cast<AGM_InGame>(GetWorld()->GetAuthGameMode());

			GameMode->Save();

			auto Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			//UGameplayStatics::OpenLevel(GetWorld(),TEXT("Cute_Zoo_3_Map"));
			auto HUD = Cast<ABAHUD>(Controller->GetHUD());
			auto ResultWidget = (Cast<ABAHUD>(Controller->GetHUD()))->GetGameResultWidget();
			FInputModeUIOnly UIOnly;

			ResultWidget->SetPlayScoreText();
			ResultWidget->SetBestScoreText();

			ResultWidget->AddToViewport();
			Controller->SetInputMode(UIOnly);
		}
	}

	for (ASpeedUpItem* PoolableItem : Items)
	{
		PoolableItem->SetDescentSpeed(Speed);
	}

	// Map Speed Synchronize
	TArray<AActor*>MapSpawners;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "MapSpawner",MapSpawners);

	if (MapSpawners.Num() > 0)
	{
		auto MapSpawner = Cast<AMapSpawner>(MapSpawners[0]);

		MapSpawner->MapComponent->SetDescentSpeed(Speed);
	}

	//BALOG(Warning,TEXT("ObstacleSpawnCooldown : %f"), ObstacleSpawnCooldown);
}

void UObjectPoolerComponent::DescentSpeedIncrease()
{
	float Speed = 0.f;
	ObstacleSpawnCooldown -= SpeedDecreaseRate * DecreaseCount;

	for (AAnimalObstacles* PoolableObstacle : Pool)
	{
		Speed = PoolableObstacle->GetDescentSpeed() + DescentSpeed * SpeedIncreaseRate;

		PoolableObstacle->SetDescentSpeed(Speed);
		//BALOG(Warning, TEXT("Descent Speed : %f"), PoolableObstacle->GetDescentSpeed());
	}

	for (ASpeedUpItem* PoolableItem : Items)
	{
		PoolableItem->SetDescentSpeed(Speed);
	}

}

void UObjectPoolerComponent::SetAnimalObstacleMesh(EPhase CurrentPhase)
{
	for (AAnimalObstacles* AnimalObstacles : Pool)
	{
		AnimalObstacles->SetAnimalMesh(CurrentPhase);
	}
}
