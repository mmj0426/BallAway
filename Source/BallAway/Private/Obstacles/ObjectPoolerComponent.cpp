
#include "Obstacles/ObjectPoolerComponent.h"
#include "Obstacle.h"


UObjectPoolerComponent::UObjectPoolerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	PoolSize = 50.f;
}

void UObjectPoolerComponent::BeginPlay()
{
	if (nullptr != PooledObjectSubClass)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			// PoolSize만큼 오브젝트 생성
			// 생성된 오브젝트는 비활성인 상태로 Pool에 들어감
			for (int i = 0; i < PoolSize; i++)
			{
				AObstacle* PoolableObstacle = World->SpawnActor<AObstacle>(PooledObjectSubClass, FVector().ZeroVector, FRotator().ZeroRotator);
				PoolableObstacle->SetActive(false);
				Pool.Add(PoolableObstacle);

			}
		}
	}

	Super::BeginPlay();	
}

AObstacle* UObjectPoolerComponent::GetPooledObject()
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
