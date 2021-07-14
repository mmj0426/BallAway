// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class BALLAWAY_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	

	AObstacle();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetLifeSpan(float newLifeSpan) override;

	FORCEINLINE class UStaticMeshComponent* GetMesh() const { return StaticMesh; }

	void SetActive(bool newActive);
	bool IsActive();

	void SetVelocity(float newVelocity);
	void SetDirection(FVector newDirection);

protected:

	class UStaticMeshComponent* StaticMesh;

	bool Active;
	float Velocity;
	FVector Direction;

	void Deactivate();

};
