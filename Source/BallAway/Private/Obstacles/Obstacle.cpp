// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Obstacle.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set Static Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObstacleMesh"));
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
	
	StaticMesh->SetCollisionProfileName(FName("NoCollision"));
	SetActorEnableCollision(true);

	// Set Box Collision
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMesh);
	BoxCollision->SetRelativeLocation(FVector(0.f,0.f,50.f));
	BoxCollision->SetWorldScale3D(FVector(1.8f));
	BoxCollision->SetCollisionProfileName(FName("OverlapOnlyPawn"));

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

		SetActorLocation(MoveVector);
	}


}

void AObstacle::SetActive(bool newActive)
{
	Active = newActive;
	SetActorEnableCollision(true);
	SetActorHiddenInGame(!newActive);
}

bool AObstacle::IsActive()
{
	return Active;
}

void AObstacle::SetDescentSpeed(float newSpeed)
{
	DescentSpeed = newSpeed;
}

void AObstacle::Deactivate()
{
	SetActive(false);
	SetActorEnableCollision(false);
	Tags.Remove("Score Calculate Obstacle");
}

