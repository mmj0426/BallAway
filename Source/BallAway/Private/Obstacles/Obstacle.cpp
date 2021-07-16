// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Obstacle.h"

#include "Kismet/KismetSystemLibrary.h"

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
		StaticMesh->SetWorldScale3D(FVector(1.8f));
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

	if (Active)
	{
		
		FVector MoveVector = FVector(GetActorLocation().X , GetActorLocation().Y - DescentSpeed, GetActorLocation().Z);
		//FLatentActionInfo LatentInfo;

		SetActorLocation(MoveVector);
		//UKismetSystemLibrary::MoveComponentTo(RootComponent, MoveVector, GetActorRotation(), false, false, 2.f, EMoveComponentAction::Type::Move, LatentInfo);
	}

}

void AObstacle::SetLifeSpan(float newLifeSpan)
{
	Lifespan = newLifeSpan;
	//UE_LOG(LogTemp, Warning, TEXT("Lifespan : %s"), Lifespan);
	GetWorldTimerManager().SetTimer(LifespanTimer, this, &AObstacle::Deactivate, Lifespan, false);
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

void AObstacle::SetDescentSpeed(float newSpeed)
{
	DescentSpeed = newSpeed;
}

void AObstacle::Deactivate()
{
	SetActive(false);
}

