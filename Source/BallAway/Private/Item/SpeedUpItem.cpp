
#include "Item/SpeedUpItem.h"

ASpeedUpItem::ASpeedUpItem()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		ItemMesh(TEXT("/Game/BasicAsset/Shape_Cube_2.Shape_Cube_2"));
	if (ItemMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(ItemMesh.Object);
		StaticMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		StaticMesh->SetWorldScale3D(FVector(1.8f));
		StaticMesh->SetSimulatePhysics(false);
	}

	StaticMesh->SetCollisionProfileName(FName("OverlapOnlyPawn"));
	SetActorEnableCollision(true);

	Active = false;

}

void ASpeedUpItem::BeginPlay()
{
	Super::BeginPlay();
}

void ASpeedUpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
