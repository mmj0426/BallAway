
#include "Obstacles/ObjectPoolerComponent.h"
#include "Obstacle.h"


UObjectPoolerComponent::UObjectPoolerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	PoolSize = 50.f;
	DescentSpeed = 2.f;
	SpeedReductionRate = 0.02f;
}

void UObjectPoolerComponent::BeginPlay()
{
	if (nullptr != PooledObjectSubClass)
	{
		UWorld* const World = GetWorld();
		if (World)
		{
			// PoolSize��ŭ ������Ʈ ����
			// ������ ������Ʈ�� ��Ȱ���� ���·� Pool�� ��
			for (int i = 0; i < PoolSize; i++)
			{
				AObstacle* PoolableObstacle = World->SpawnActor<AObstacle>(PooledObjectSubClass, FVector().ZeroVector, FRotator().ZeroRotator);
				PoolableObstacle->SetActive(false);
				PoolableObstacle->SetDescentSpeed(DescentSpeed);
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

void UObjectPoolerComponent::DescentSpeedReduction()
{
	for (AObstacle* PoolableObstacle : Pool)
	{
		PoolableObstacle->SetDescentSpeed(PoolableObstacle->GetDescentSpeed() - DescentSpeed * SpeedReductionRate);
		BALOG(Warning,TEXT("Speed : %f"), PoolableObstacle->GetDescentSpeed());
	}

}