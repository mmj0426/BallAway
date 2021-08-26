#pragma once

#include "../BallAway.h"
#include "GameFramework/Actor.h"
#include "MapSpawner.generated.h"

class AMapActor;
class UMapSpawnerComponent;

UCLASS()
class BALLAWAY_API AMapSpawner : public AActor
{
	GENERATED_BODY()
	
public:	

	AMapSpawner();

	virtual void BeginPlay() override;

	void MapSpawn(float LeftLocY, float RightLocY);

	UPROPERTY(EditAnywhere, Category = Spawner)
	UMapSpawnerComponent* MapComponent;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private : 

	UPROPERTY(EditAnywhere)
	class UBoxComponent* LeftSpawnVolume;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* RightSpawnVolume;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* ActivateVolume;


};
