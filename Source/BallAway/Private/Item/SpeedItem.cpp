// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/SpeedItem.h"

ASpeedItem:: ASpeedItem()
{
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemVisual"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>
		CubeMesh(TEXT("/Game/BasicAsset/Shape_Cube_2.Shape_Cube_2"));

	if (CubeMesh.Succeeded())
	{
		StaticMesh->SetStaticMesh(CubeMesh.Object);
		StaticMesh->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
		StaticMesh->SetWorldScale3D(FVector(1.8f));
		StaticMesh->SetSimulatePhysics(false);
	}

	RootComponent = StaticMesh;
	SetActorEnableCollision(true);
}

void ASpeedItem::BeginPlay()
{
}

void ASpeedItem::Tick(float DeltaTime)
{
}
