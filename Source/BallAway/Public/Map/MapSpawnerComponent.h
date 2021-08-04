#pragma once

#include "../BallAway.h"
#include "Components/ActorComponent.h"
#include "MapSpawnerComponent.generated.h"

class AMapActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BALLAWAY_API UMapSpawnerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMapSpawnerComponent();
	
	virtual void BeginPlay() override;

	AMapActor* GetLeftMaps();
	AMapActor* GetRightMaps();

private : 

	int32 SpawnSize;

	TArray<AMapActor*> LeftMaps;
	TArray<AMapActor*> RightMaps;

	UPROPERTY(EditAnywhere, Category = "Map")
		TSubclassOf<class AMapActor> LeftMap1;

	UPROPERTY(EditAnywhere, Category = "Map")
		TSubclassOf<class AMapActor> LeftMap2;

	UPROPERTY(EditAnywhere, Category = "Map")
		TSubclassOf<class AMapActor> RightMap1;

	UPROPERTY(EditAnywhere, Category = "Map")
		TSubclassOf<class AMapActor> RightMap2;


};
