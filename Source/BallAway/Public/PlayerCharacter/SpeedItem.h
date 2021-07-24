// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"

#include "Obstacle.h"

#include "GameFramework/Actor.h"
#include "SpeedItem.generated.h"

class AObstacle;

UCLASS()
class BALLAWAY_API ASpeedItem : public AObstacle
{
	GENERATED_BODY()
	
public:	

	ASpeedItem();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;




};
