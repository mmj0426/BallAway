#include "PlayerCharacter.h"
#include "Math/UnrealMathUtility.h"

#include "Components/StaticMeshComponent.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("%f"), MoveDirection.X));


}
