
#pragma once

#include "../BallAway.h"
#include "Obstacles/Obstacle.h"
#include "SpeedUpItem.generated.h"

UCLASS()
class BALLAWAY_API ASpeedUpItem : public AObstacle
{
	GENERATED_BODY()
	
public : 
	ASpeedUpItem();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
