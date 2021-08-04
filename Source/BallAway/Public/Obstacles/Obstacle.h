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

	// 활성화
	bool Active;
	bool IsActive();
	void SetActive(bool newActive);
	void Deactivate();

	// 하강 속도
	float DescentSpeed;
	void SetDescentSpeed(float newSpeed);

	// Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* StaticMesh;

	FORCEINLINE float GetDescentSpeed() const { return DescentSpeed; }

	// Collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	class UBoxComponent* BoxCollision;
};
