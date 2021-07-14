// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Obstacle.h"

// Sets default values
AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	Velocity = 100.f;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
	CubeMesh(TEXT("/Game/BasicAsset/Shape_Cube.Shape_Cube"));
	if (CubeMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(CubeMesh.Object);
		StaticMesh->SetRelativeLocation(FVector(0.f,0.f,0.f));
		StaticMesh->SetWorldScale3D(FVector(1.f));
		StaticMesh->SetSimulatePhysics(false);
	}

	RootComponent = StaticMesh;
	SetActorEnableCollision(true);

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::SetLifeSpan(float newLifeSpan)
{
}

void AObstacle::SetActive(bool newActive)
{
	Active = newActive;
	SetActorHiddenInGame(!newActive);
}

bool AObstacle::IsActive()
{
	return Active;
}

void AObstacle::SetVelocity(float newVelocity)
{
	Velocity = newVelocity;
}

void AObstacle::SetDirection(FVector newDirection)
{
	Direction = newDirection;
}

void AObstacle::Deactivate()
{
	SetActive(false);
}

