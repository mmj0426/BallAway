// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "Components/ActorComponent.h"

#include "ObjectPoolerComponent.generated.h"

class AObstacle;
class ASpeedUpItem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BALLAWAY_API UObjectPoolerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UObjectPoolerComponent();
	virtual void BeginPlay() override;

	AObstacle* GetPooledObstacle();
	ASpeedUpItem* GetPooledItem();

	UFUNCTION()
	void DescentSpeedDecrease();

	UFUNCTION()
	void DescentSpeedIncrease();

	FORCEINLINE float GetSpeedReductionRate() const {return SpeedDecreaseRate;}

	// 스폰 쿨타임
	UPROPERTY(EditAnywhere,Category = "Obstacle Speed")
	float ObstacleSpawnCooldown;

private:

	UPROPERTY(EditAnywhere, Category = ObjectPooler)
	TSubclassOf<class AObstacle> ObstacleSubClass;

	UPROPERTY(EditAnywhere, Category = ObjectPooler)
	TSubclassOf<class ASpeedUpItem> ItemSubClass;

	UPROPERTY(EditAnywhere, Category = "ObjectPooler")
	int PoolSize;

	UPROPERTY(EditAnywhere, Category = "ObjectPooler")
	int ItemPoolSize;

	// 하강 속도
	UPROPERTY(EditAnywhere, Category = "Obstacle Speed")
	float DescentSpeed;
		
	TArray<AObstacle*> Pool;
	TArray<ASpeedUpItem*>Items;

	// 속력 감소율
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle Speed", meta = (AllowPrivateAccess = true))
	float SpeedDecreaseRate;

	// 속력 증가율
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle Speed", meta = (AllowPrivateAccess = true))
	float SpeedIncreaseRate;

};
