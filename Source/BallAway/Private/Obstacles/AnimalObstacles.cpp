// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/AnimalObstacles.h"

#include "PlayerCharacter/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

AAnimalObstacles::AAnimalObstacles()
{
	PrimaryActorTick.bCanEverTick = true;

	AnimalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("AnimalMesh"));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_Bull(TEXT("/Game/Cute_Zoo_3/Meshes/SK_Bull.SK_Bull"));
	if (SK_Bull.Succeeded())
	{
		BullMesh = SK_Bull.Object;
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_Mule(TEXT("/Game/Cute_Zoo_3/Meshes/SK_Mule.SK_Mule"));
	if (SK_Mule.Succeeded())
	{
		MuleMesh = SK_Mule.Object;
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>
		SK_Ostrich(TEXT("/Game/Cute_Zoo_3/Meshes/SK_Ostrich.SK_Ostrich"));
	if (SK_Ostrich.Succeeded())
	{
		OstrichMesh = SK_Ostrich.Object;
	}

	AnimalMesh->SetSkeletalMesh(MuleMesh);
	
	AnimalMesh->SetupAttachment(BoxCollision);
}

void AAnimalObstacles::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAnimalObstacles::OnOverlapBegin);
}

void AAnimalObstacles::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AAnimalObstacles::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto PlayerCharacter = Cast<APlayerCharacter>(OtherActor);

	if (nullptr != PlayerCharacter)
	{
		OnHitPlayer.Broadcast();
	}
}