// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/PC_PlayerCharacter.h"
#include "PlayerCharacter/PlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

void APC_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	BAPlayer = Cast<APlayerCharacter>(GetPawn());
}

void APC_PlayerCharacter::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindTouch(IE_Pressed, this, &APC_PlayerCharacter::OnTouchBegin);
	InputComponent->BindTouch(IE_Repeat, this, &APC_PlayerCharacter::OnTouchTick);
	InputComponent->BindTouch(IE_Released, this, &APC_PlayerCharacter::OnTouchEnd);
}

void APC_PlayerCharacter::OnTouchBegin(ETouchIndex::Type TouchIndex, FVector TouchLocation)
{
	FirstLocation = TouchLocation;

	// 처음 터치.X ~ 현재 플레이어.X 까지의 거리
	DistanceToPlayer = FMath::Abs(FirstLocation.X - BAPlayer->GetActorLocation().X);
}

void APC_PlayerCharacter::OnTouchTick(ETouchIndex::Type TouchIndex, FVector TouchLocation)
{

	if (FMath::Abs(DesiredLocation.X - BAPlayer->GetActorLocation().X) > 50.f)
	{
		if (MoveDirection.X < 0.f)
		{
			BAPlayer->AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::Y), -1.f);
		}
		else if (MoveDirection.X > 0.f)
		{
			BAPlayer->AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::Y), 1.f);
		}
	}

	CurrentLocation = TouchLocation;

	DistanceFromTouch = FMath::Abs(FirstLocation.X - CurrentLocation.X);

	MoveDirection = (CurrentLocation - FirstLocation).GetSafeNormal();

	DesiredLocation = FVector(BAPlayer->GetActorLocation().X + DistanceFromTouch, BAPlayer->GetActorLocation().Y, BAPlayer->GetActorLocation().Z);

	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("%f"), FMath::Abs(GetActorLocation().Y - DesiredLocation.Y)));
	//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("%f"), GetActorLocation().Y));


	// GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("%f"), Direction.X));

	//AddMovementInput(FRotationMatrix(FRotator(0.f, GetControlRotation().Yaw, 0.f)).GetUnitAxis(EAxis::Y), 1.f);
}

void APC_PlayerCharacter::OnTouchEnd(ETouchIndex::Type TouchIndex, FVector TouchLocation)
{
	FirstLocation = FVector::ZeroVector;
	CurrentLocation = FVector::ZeroVector;
	MoveDirection = FVector::ZeroVector;
}
