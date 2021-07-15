// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

class UObjectPoolerComponent;

UCLASS()
class BALLAWAY_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

	virtual void BeginPlay() override;

private:
	FVector GetRandomPointInVolume();
	float GetLifespanVal();

	class UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere, Category = Spawner)
	UObjectPoolerComponent* ObjectPooler;

	//UPROPERTY(EditAnywhere, Category = Spawner)
	//float LifespanMin;

	//UPROPERTY(EditAnywhere, Category = Spawner)
	//float LifespanMax;

	UPROPERTY(EditAnywhere, Category = Spawner)
	float SpawnCooldown;

	UPROPERTY(EditAnywhere, Category = Spawner)
	bool SparkingMode;

	UPROPERTY(EditAnywhere, Category = Spawner)
	float SparklesVelocity;

	FTimerHandle SpawnCooldownTimer;

	void Spawn();

};
