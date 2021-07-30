
#include "Obstacles/ObjectPoolerComponent.h"
#include "Obstacle.h"
#include "Item/SpeedUpItem.h"


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
