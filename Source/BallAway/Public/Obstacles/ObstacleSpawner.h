// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "PhaseEnum.h"

#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

class UObjectPoolerComponent;
class AGM_InGame;

UCLASS()
class BALLAWAY_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

	virtual void BeginPlay() override;

private:

	class UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* DeactivateVolume;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = Spawner)
	UObjectPoolerComponent* ObjectPooler;

	UPROPERTY(EditAnywhere, Category = Spawner)
	float SpawnCooldown;

	void DecideObstacleSize();
	void ChooseSpawnLine();
	void Spawn();

private : 

	// ��ֹ� ���� ���� ����
	FTimerHandle SpawnCooldownTimer;

	TArray<int32> SpawnLineNumber;

	int32 SpawnObstacleNumber;
	int32 ObstacleMin;
	int32 ObstacleMax;
	int32 LineNumMax;

	// ������ ���� ����
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Phase", meta = (AllowPrivateAccess = true))
	EPhase CurrentPhase;


};
