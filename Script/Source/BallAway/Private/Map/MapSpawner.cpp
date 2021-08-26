
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
	
	ActivateVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("ActivateVolume"));
	ActivateVolume->OnComponentBeginOverlap.AddDynamic(this, &AMapSpawner::OnOverlapBegin);

	MapComponent = CreateDefaultSubobject<UMapSpawnerComponent>(TEXT("MapComponent"));

	this->Tags.Add(TEXT("MapSpawner"));

}

void AMapSpawner::BeginPlay()
{
	Super::BeginPlay();

	MapSpawn(LeftSpawnVolume->GetComponentLocation().Y, RightSpawnVolume->GetComponentLocation().Y);

	
}

void AMapSpawner::MapSpawn(float LeftLocY, float RightLocY)
{
	// Left Map
	AMapActor* LeftMapActor = MapComponent->GetLeftMaps();
	
	if (nullptr == LeftMapActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot spawn - object pool drained."));
		return;
	}

	FVector LeftLocation = FVector(LeftSpawnVolume->GetComponentLocation().X, LeftLocY, 30.f);

	LeftMapActor->SetActorLocation(LeftLocation);
	LeftMapActor->SetActive(true);

	// Right Map
	AMapActor* RightMapActor = MapComponent->GetRightMaps();

	if (nullptr == RightMapActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cannot spawn - object pool drained."));
		return;
	}

	FVector RightLocation = FVector(RightSpawnVolume->GetComponentLocation().X, RightLocY, 30.f);

	RightMapActor->SetActorLocation(RightLocation);
	RightMapActor->SetActive(true);

}

void AMapSpawner::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto MapActor = Cast<AMapActor>(OtherActor);

	if (nullptr != MapActor && OtherComp->ComponentHasTag(TEXT("MapSpawn")))
	{
		MapSpawn(LeftSpawnVolume->GetComponentLocation().Y + 1800.f, RightSpawnVolume->GetComponentLocation().Y + 1800.f);
	}

	if (nullptr != MapActor && OtherComp->ComponentHasTag(TEXT("Deactivate")))
	{
		MapActor->Deactivate();
	}
}


