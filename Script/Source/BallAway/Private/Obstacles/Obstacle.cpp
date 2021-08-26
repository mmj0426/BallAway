#include "Obstacles/Obstacle.h"

#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values
AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	SetActorEnableCollision(true);

	// Set Box Collision
	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->SetupAttachment(StaticMesh);
	SphereCollision->SetRelativeLocation(FVector(0.f, 0.f, 30.f));
	SphereCollision->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
	SphereCollision->SetWorldScale3D(FVector(3.f));
	SphereCollision->SetCollisionProfileName(FName("OverlapOnlyPawn"));

	RootComponent = SphereCollision;
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
		FVector MoveVector = FVector(GetActorLocation().X, GetActorLocation().Y - DescentSpeed, GetActorLocation().Z);

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
