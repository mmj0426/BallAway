// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "PhaseEnum.h"

#include "GameFramework/Actor.h"
#include "ObstacleSpawner.generated.h"

class UObjectPoolerComponent;
class AGM_InGame;


//DECLARE_MULTICAST_DELEGATE(FSpeedReductionDelegate);

UCLASS()
class BALLAWAY_API AObstacleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacleSpawner();

	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* SpawnVolume;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* DeactivateVolume;

	UFUNCTION()
	void DeactivateOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 플레이어를 스폰하기 위해 잠시 정지
	UPROPERTY(EditAnywhere)
	class UBoxComponent* PauseVolume;

	UFUNCTION()
	void PauseOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = Spawner)
	UObjectPoolerComponent* ObjectPooler;

	UPROPERTY(EditAnywhere, Category = Spawner)
	float ItemSpawnCooldown;

	void DecideObstacleSize();
	void ChooseSpawnLine();
	void Spawn();

	// 아이템 생성 여부 검사
	void SetCanItemSpawn();

private : 

	// 장애물 스폰 관련 변수
	FTimerHandle ObstacleSpawnCooldownTimer;
	
	TArray<int32> SpawnLineNumber;

	int32 SpawnObstacleNumber;
	int32 ObstacleMin;
	int32 ObstacleMax;
	int32 LineNumMax;

	// 페이즈 관련 변수
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Phase", meta = (AllowPrivateAccess = true))
	EPhase CurrentPhase;

	// 아이템 관련 변수
	FTimerHandle ItemSpawnCooldownTimer;

	bool CanItemSpawn;
	int32 ItemSpawnLine;

	// PauseVolume 변수
	bool IsFirstOverlap;

};
