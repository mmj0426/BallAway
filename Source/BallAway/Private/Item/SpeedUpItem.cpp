
#include "Item/SpeedUpItem.h"
#include "PlayerCharacter/PlayerCharacter.h"
#include "Components/BoxComponent.h"

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
}

void ASpeedUpItem::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ASpeedUpItem::OnOverlapBegin);
}

void ASpeedUpItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpeedUpItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//BALOG(Warning, TEXT("OnOverlapBegin"));
	auto PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

	if(nullptr != PlayerCharacter)
	{
		Deactivate();
		OnGetItem.Broadcast();
	}
}
