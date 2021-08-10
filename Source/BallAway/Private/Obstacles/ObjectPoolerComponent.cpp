
#include "Obstacles/ObjectPoolerComponent.h"
#include "Obstacle.h"
#include "Item/SpeedUpItem.h"

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
			// PoolSize만큼 오브젝트 생성
			// 생성된 오브젝트는 비활성인 상태로 Pool에 들어감
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
				// Speed Up 아이템을 플레이어가 먹을 시 DescentSpeedIncrease 함수 호출
				SpeedUpItem->OnGetItem.AddUObject(this, &UObjectPoolerComponent::DescentSpeedIncrease);
				Items.Add(SpeedUpItem);
			}
		}
	}

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
	ObstacleSpawnCooldown += SpeedIncreaseRate;

	for (AObstacle* PoolableObstacle : Pool)
	{
		PoolableObstacle->SetDescentSpeed(PoolableObstacle->GetDescentSpeed() - DescentSpeed * SpeedDecreaseRate);

		// 속도가 0 이하일 때 GameOver UI 띄움
		if (PoolableObstacle->ActorHasTag("GameOver Obstacle") && PoolableObstacle->GetDescentSpeed() <= 0.f)
		{
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

		//BALOG(Warning, TEXT("Descent Speed : %f"), PoolableObstacle->GetDescentSpeed());
	}

	for (ASpeedUpItem* PoolableItem : Items)
	{
		PoolableItem->SetDescentSpeed(PoolableItem->GetDescentSpeed() - DescentSpeed * SpeedDecreaseRate);
	}
}

void UObjectPoolerComponent::DescentSpeedIncrease()
{
	ObstacleSpawnCooldown -= SpeedIncreaseRate;

	for (AObstacle* PoolableObstacle : Pool)
	{
		PoolableObstacle->SetDescentSpeed(PoolableObstacle->GetDescentSpeed() + DescentSpeed * SpeedIncreaseRate);
		//BALOG(Warning, TEXT("Descent Speed : %f"), PoolableObstacle->GetDescentSpeed());
	}

	for (ASpeedUpItem* PoolableItem : Items)
	{
		PoolableItem->SetDescentSpeed(PoolableItem->GetDescentSpeed() + DescentSpeed * SpeedIncreaseRate);
	}
}
