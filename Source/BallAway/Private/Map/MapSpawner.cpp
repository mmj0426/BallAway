
#include "Map/MapSpawner.h"
#include "Map/MapActor.h"
#include "Map/MapSpawnerComponent.h"

#include "Components/BoxComponent.h"


AMapSpawner::AMapSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	LeftSpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftSpawnVolume"));
	RootComponent = LeftSpawnVolume;

	RightSpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("RightSpawnVolume"));
	RightSpawnVolume->SetRelativeLocation(FVector(-2000.f,0.f,0.f));
	
	MapComponent = CreateDefaultSubobject<UMapSpawnerComponent>(TEXT("MapComponent"));

	this->Tags.Add(TEXT("MapSpawner"));

}

void AMapSpawner::BeginPlay()
{
	Super::BeginPlay();

	MapSpawn();
	
}

void AMapSpawner::MapSpawn()
{
	// Left Map
	AMapActor* LeftMapActor = MapComponent->GetLeftMaps();
	
	if (nullptr == LeftMapActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot spawn - object pool drained."));
		return;
	}

	FVector LeftLocation = FVector(LeftSpawnVolume->GetComponentLocation().X, LeftSpawnVolume->GetComponentLocation().Y, 30.f);

	BALOG(Warning, TEXT("LeftLocation : %f, %f"), -LeftSpawnVolume->Bounds.BoxExtent.X, -LeftSpawnVolume->Bounds.BoxExtent.Y)

	LeftMapActor->SetActorLocation(LeftLocation);
	LeftMapActor->SetActive(true);

	// Right Map
	AMapActor* RightMapActor = MapComponent->GetRightMaps();

	if (nullptr == RightMapActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot spawn - object pool drained."));
		return;
	}

	FVector RightLocation = FVector(RightSpawnVolume->GetComponentLocation().X, RightSpawnVolume->GetComponentLocation().Y, 30.f);

	RightMapActor->SetActorLocation(RightLocation);
	RightMapActor->SetActive(true);

}

