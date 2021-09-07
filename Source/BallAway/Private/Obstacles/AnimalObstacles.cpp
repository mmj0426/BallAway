// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacles/AnimalObstacles.h"

#include "PlayerCharacter/PlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimationAsset.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AAnimalObstacles::AAnimalObstacles()
{
	PrimaryActorTick.bCanEverTick = true;

	// Set Skeletal Mesh
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
		
	AnimalMesh->SetupAttachment(SphereCollision);
	AnimalMesh->SetSkeletalMesh(MuleMesh);
	AnimalMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -30.f), FRotator(0.f, 180.f, 0.f));

	AnimalMesh->SetRelativeScale3D(FVector(0.35f));

	// Camera Shake
	//static ConstructorHelpers::FClassFinder<UMatineeCameraShake>
	//CameraShake(TEXT("/Game/Blueprints/CS_CollisionWithPlayer.CS_CollisionWithPlayer"));
	//if (CameraShake.Succeeded())
	//{
	//	CS_CollisionWithPlayer = CameraShake.Class;
	//}
}

void AAnimalObstacles::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AAnimalObstacles::OnOverlapBegin);
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
		// 카메라 쉐이크
		//TArray<AActor*> Cameras;
		//UGameplayStatics::GetAllActorsWithTag(GetWorld(), "WorldCamera", Cameras);
		//if (Cameras.Num() > 0)
		//{
		//	//UGameplayStatics::PlayWorldCameraShake(GetWorld(),CS_CollisionWithPlayer,Cameras[0]->GetActorLocation(),800.f,2500.f,1.f,false);
		//	
		//}
		//GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(CS_CollisionWithPlayer);
		OnHitPlayer.Broadcast();
	}
}

void AAnimalObstacles::SetAnimalMesh(EPhase CurrentPhase)
{
	switch (CurrentPhase)
	{
	case EPhase::Phase1:
		BALOG(Warning, TEXT("Mule"));
		AnimalMesh->SetSkeletalMesh(MuleMesh);
		AnimalMesh->SetRelativeLocationAndRotation(FVector(0.f,0.f,-33.f), FRotator(0.f, 180.f,0.f));
		AnimalMesh->SetRelativeScale3D(FVector(0.5f));

		AnimalMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
		MuleRunAnim = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Cute_Zoo_3/Animations/Mule/Anim_Mule_Run.Anim_Mule_Run"));
		if (nullptr != MuleRunAnim)
		{
			AnimalMesh->PlayAnimation(MuleRunAnim, true);
		}

		break;

	case EPhase::Phase2:
		BALOG(Warning, TEXT("Ostrich"));
		AnimalMesh->SetSkeletalMesh(OstrichMesh);
		AnimalMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -33.f), FRotator(0.f, 180.f, 0.f));
		AnimalMesh->SetRelativeScale3D(FVector(1.f));

		AnimalMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
		OstrichRunAnim = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Cute_Zoo_3/Animations/Ostrich/Animal_Ostrich_Run.Animal_Ostrich_Run"));
		if (nullptr != OstrichRunAnim)
		{
			AnimalMesh->PlayAnimation(OstrichRunAnim, true);
		}

		break;

	case EPhase::Phase3:
		BALOG(Warning, TEXT("Bull"));
		AnimalMesh->SetSkeletalMesh(BullMesh);
		AnimalMesh->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -33.f), FRotator(0.f, 180.f, 0.f));
		AnimalMesh->SetRelativeScale3D(FVector(0.5f));

		AnimalMesh->SetAnimationMode(EAnimationMode::AnimationSingleNode);
		BullRunAnim = LoadObject<UAnimationAsset>(nullptr, TEXT("/Game/Cute_Zoo_3/Animations/Bull/Anim_Bull_Run.Anim_Bull_Run"));
		if (nullptr != BullRunAnim)
		{
			AnimalMesh->PlayAnimation(BullRunAnim,true);
		}

		break;

	default:
		break;
	}

}
