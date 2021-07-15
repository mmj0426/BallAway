// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "Components/ActorComponent.h"

#include "ObjectPoolerComponent.generated.h"

class AObstacle;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BALLAWAY_API UObjectPoolerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UObjectPoolerComponent();
	virtual void BeginPlay() override;

	AObstacle* GetPooledObject();

private:

	UPROPERTY(EditAnywhere, Category = ObjectPooler)
	TSubclassOf<class AObstacle> PooledObjectSubClass;

	UPROPERTY(EditAnywhere, Category = ObjectPooler)
	int PoolSize;

	TArray<AObstacle*> Pool;


		
};
