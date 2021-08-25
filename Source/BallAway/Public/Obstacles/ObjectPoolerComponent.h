#pragma once

#include "../BallAway.h"
#include "Components/ActorComponent.h"

#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"

#include "Obstacles/PhaseEnum.h"
#include "ObjectPoolerComponent.generated.h"

class AObstacle;
class AAnimalObstacles;
class ASpeedUpItem;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BALLAWAY_API UObjectPoolerComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UObjectPoolerComponent();
	virtual void BeginPlay() override;

	AAnimalObstacles* GetPooledObstacle();
	ASpeedUpItem* GetPooledItem();

	UFUNCTION()
		void DescentSpeedDecrease();

	UFUNCTION()
		void DescentSpeedIncrease();

	UFUNCTION()
		void SetSpeed(float Speed);

	FORCEINLINE float GetSpeedReductionRate() const { return SpeedDecreaseRate; }
	FORCEINLINE float GetDescentSpeed() const { return DescentSpeed; }

	// Skeletal Mesh 변경
	void SetAnimalObstacleMesh(EPhase CurrentPhase);

	// 스폰 쿨타임
	UPROPERTY(EditAnywhere, Category = "Obstacle Speed")
		float ObstacleSpawnCooldown;

private:

	UPROPERTY(EditAnywhere, Category = ObjectPooler)
		TSubclassOf<class AAnimalObstacles> ObstacleSubClass;

	UPROPERTY(EditAnywhere, Category = ObjectPooler)
		TSubclassOf<class ASpeedUpItem> ItemSubClass;

	UPROPERTY(EditAnywhere, Category = "ObjectPooler")
		int PoolSize;

	UPROPERTY(EditAnywhere, Category = "ObjectPooler")
		int ItemPoolSize;

	// 하강 속도
	UPROPERTY(EditAnywhere, Category = "Obstacle Speed")
		float DescentSpeed;

	TArray<AAnimalObstacles*> Pool;
	TArray<ASpeedUpItem*>Items;

	// 속력 감소율
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle Speed", meta = (AllowPrivateAccess = true))
		float SpeedDecreaseRate;

	int32 DecreaseCount;

	// 속력 증가율
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Obstacle Speed", meta = (AllowPrivateAccess = true))
		float SpeedIncreaseRate;


	UAudioComponent* WalkAudio;
	UAudioComponent* RunAudio;

	USoundCue* Walk_Sound;
	USoundCue* Run_Sound;
};