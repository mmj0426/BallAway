// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "Obstacles/Obstacle.h"
#include "ItemBase.generated.h"

/**
 * 
 */
UCLASS()
class BALLAWAY_API AItemBase : public AObstacle
{
	GENERATED_BODY()

public : 
	AItemBase();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

};
