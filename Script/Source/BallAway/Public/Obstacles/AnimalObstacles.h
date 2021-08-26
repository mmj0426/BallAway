// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BallAway.h"
#include "Obstacles/Obstacle.h"
#include "Obstacles/PhaseEnum.h"
#include "AnimalObstacles.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHitPlayer);

UCLASS()
class BALLAWAY_API AAnimalObstacles : public AObstacle
{
	GENERATED_BODY()

public:
	AAnimalObstacles();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetAnimalMesh(EPhase CurrentPhase);

	FOnHitPlayer OnHitPlayer;

	// Skeletal Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class USkeletalMeshComponent* AnimalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class USkeletalMesh* BullMesh;
		
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class USkeletalMesh* MuleMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class USkeletalMesh* OstrichMesh;

	// Animation Asset
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimationAsset* BullRunAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimationAsset* MuleRunAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	class UAnimationAsset* OstrichRunAnim;

	// Camera Shake
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera Shake")
	TSubclassOf<UMatineeCameraShake> CS_CollisionWithPlayer;

};
