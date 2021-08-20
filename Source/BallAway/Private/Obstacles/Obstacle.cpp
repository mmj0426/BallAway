// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/Obstacle.h"

#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	SetActorEnableCollision(true);

	// Set Box Collision
<<<<<<< HEAD
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(StaticMesh);
	BoxCollision->SetRelativeLocation(FVector(0.f,0.f,50.f));
	BoxCollision->SetRelativeRotation(FRotator(0.f,0.f,180.f));
	BoxCollision->SetWorldScale3D(FVector(1.8f));
	BoxCollision->SetCollisionProfileName(FName("OverlapOnlyPawn"));

=======
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(StaticMesh);
	SphereCollision->SetRelativeLocation(FVector(0.f,0.f,30.f));
	SphereCollision->SetRelativeRotation(FRotator(0.f,0.f,0.f));
	SphereCollision->SetWorldScale3D(FVector(3.f));
	SphereCollision->SetCollisionProfileName(FName("OverlapOnlyPawn"));

	RootComponent = SphereCollision;
>>>>>>> feacher/Obstacles
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

