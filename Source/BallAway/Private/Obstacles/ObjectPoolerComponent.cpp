
#include "Obstacles/ObjectPoolerComponent.h"
#include "Obstacle.h"
#include "Item/SpeedUpItem.h"

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
				AObstacle* PoolableObstacle = World->SpawnActor<AObstacle>(ObstacleSubClass, FVector().ZeroVector, FRotator().ZeroRotator);
				PoolableObstacle->SetActive(false);
				PoolableObstacle->SetDescentSpeed(DescentSpeed);
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

<<<<<<< HEAD
=======
	// Map Speed Synchronize
	TArray<AActor*>MapSpawners;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "MapSpawner", MapSpawners);

	if (MapSpawners.Num() > 0)
	{
		//BALOG(Warning, TEXT("asdf"));
		auto MapSpawner = Cast<AMapSpawner>(MapSpawners[0]);

		MapSpawner->MapComponent->SetDescentSpeed(DescentSpeed);
	}

>>>>>>> feacher/Obstacles
	Super::BeginPlay();	
}

AObstacle* UObjectPoolerComponent::GetPooledObstacle()
{
	for (AObstacle* PoolableObstacle : Pool)
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
<<<<<<< HEAD
	ObstacleSpawnCooldown += SpeedIncreaseRate;

	for (AObstacle* PoolableObstacle : Pool)
	{
		PoolableObstacle->SetDescentSpeed(PoolableObstacle->GetDescentSpeed() - DescentSpeed * SpeedDecreaseRate);
=======
	float Speed = 0.f;

	//ObstacleSpawnCooldown += SpeedDecreaseRate;
	DecreaseCount++;
	ObstacleSpawnCooldown = FMath::Clamp<float>(ObstacleSpawnCooldown + SpeedDecreaseRate, 0.5, 5);

	for (AAnimalObstacles* PoolableObstacle : Pool)
	{
		//Speed = FMath::Clamp<float>(PoolableObstacle->GetDescentSpeed() - DescentSpeed * SpeedDecreaseRate * DecreaseCount,0,DescentSpeed);
		Speed = FMath::Clamp<float>(PoolableObstacle->GetDescentSpeed() * (1- SpeedDecreaseRate), 0, DescentSpeed);
		PoolableObstacle->SetDescentSpeed(Speed);
>>>>>>> feacher/Obstacles

		// �ӵ��� 0 ������ �� GameOver UI ���
		if (PoolableObstacle->ActorHasTag("GameOver Obstacle") && PoolableObstacle->GetDescentSpeed() <= 3.f)
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
		PoolableItem->SetDescentSpeed(PoolableItem->GetDescentSpeed() - DescentSpeed * SpeedDecreaseRate);
	}
<<<<<<< HEAD
=======

	// Map Speed Synchronize
	TArray<AActor*>MapSpawners;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "MapSpawner",MapSpawners);

	if (MapSpawners.Num() > 0)
	{
		auto MapSpawner = Cast<AMapSpawner>(MapSpawners[0]);

		MapSpawner->MapComponent->SetDescentSpeed(Speed);
	}

	//BALOG(Warning,TEXT("ObstacleSpawnCooldown : %f"), ObstacleSpawnCooldown);
>>>>>>> feacher/Obstacles
}

void UObjectPoolerComponent::DescentSpeedIncrease()
{
	float Speed = 0.f;
	//ObstacleSpawnCooldown -= SpeedDecreaseRate * DecreaseCount;
	ObstacleSpawnCooldown = FMath::Clamp<float>(ObstacleSpawnCooldown - SpeedDecreaseRate * DecreaseCount, 0.7,5);

	for (AObstacle* PoolableObstacle : Pool)
	{
		Speed = PoolableObstacle->GetDescentSpeed() + DescentSpeed * SpeedIncreaseRate;

		PoolableObstacle->SetDescentSpeed(Speed);
		//BALOG(Warning, TEXT("Descent Speed : %f"), PoolableObstacle->GetDescentSpeed());
	}

	for (ASpeedUpItem* PoolableItem : Items)
	{
		PoolableItem->SetDescentSpeed(Speed);
	}

	TArray<AActor*>MapSpawners;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "MapSpawner", MapSpawners);

	if (MapSpawners.Num() > 0)
	{
		auto MapSpawner = Cast<AMapSpawner>(MapSpawners[0]);

		MapSpawner->MapComponent->SetDescentSpeed(Speed);
	}

}

void UObjectPoolerComponent::SetSpeed(float Speed)
{

	for (AAnimalObstacles* PoolableObstacle : Pool)
	{
		PoolableObstacle->SetDescentSpeed(Speed);
	}

	TArray<AActor*>MapSpawners;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "MapSpawner", MapSpawners);

	if (MapSpawners.Num() > 0)
	{
		auto MapSpawner = Cast<AMapSpawner>(MapSpawners[0]);

		MapSpawner->MapComponent->SetDescentSpeed(Speed);
	}

}
