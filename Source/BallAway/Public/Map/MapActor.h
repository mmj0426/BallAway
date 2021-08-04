#pragma once

#include "../BallAway.h"
#include "Obstacles/Obstacle.h"
#include "MapActor.generated.h"

UCLASS()
class BALLAWAY_API AMapActor : public AObstacle
{
	GENERATED_BODY()
	
public:	

	AMapActor();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
