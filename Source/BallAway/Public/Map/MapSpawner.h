// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "GameFramework/Actor.h"
#include "MapSpawner.generated.h"

UCLASS()
class BALLAWAY_API AMapSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMapSpawner();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

};
