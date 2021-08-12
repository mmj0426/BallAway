// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter/PC_PlayerCharacter.h"
#include "PlayerCharacter/PlayerCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void APC_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

	BAPlayer = Cast<APlayerCharacter>(GetPawn());

	IsPlayerSpawned = false;

}

void APC_PlayerCharacter::Tick(float DeltaTime)
{
	// 플레이어의 위치 (월드좌표)를 스크린 좌표로 바꿈
	ProjectWorldLocationToScreen(BAPlayer->GetActorLocation(), PlayerScreenLocation);

	//BALOG(Warning, TEXT("Touch : %f, Player : %f"), CurrentLocation.X, PlayerScreenLocation.X);
	//BALOG(Error, TEXT("MoveDirection.X : %f"), FMath::Abs(CurrentLocation.X - PlayerScreenLocation.X));

	if (FMath::Abs(CurrentLocation.X - PlayerScreenLocation.X) > 10.f && IsPlayerSpawned)
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
	// 첫 터치 위치
	CurrentLocation = (FVector2D)TouchLocation;

	MoveDirection = (CurrentLocation - PlayerScreenLocation).GetSafeNormal();
	ProjectWorldLocationToScreen(BAPlayer->GetActorLocation(), PlayerScreenLocation);

	if (!IsPlayerSpawned)
	{
		FHitResult Hit;
		FVector2D ScreenLocation = FVector2D(CurrentLocation.X, PlayerScreenLocation.Y);
		GetHitResultAtScreenPosition(ScreenLocation, ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			BAPlayer->SetActorLocation(FVector(Hit.ImpactPoint.X, BAPlayer->GetActorLocation().Y, BAPlayer->GetActorLocation().Z));
			BAPlayer->SetActorHiddenInGame(false);

			IsPlayerSpawned = true;

			OnPlayerSpawned.Broadcast();
		}

	}

}

void APC_PlayerCharacter::OnTouchTick(ETouchIndex::Type TouchIndex, FVector TouchLocation)
{
	if (IsPlayerSpawned)
	{
		// 현재 터치 위치
		CurrentLocation = (FVector2D)TouchLocation;

		// 공이 움직여야할 방향 (좌, 우)
		MoveDirection = (CurrentLocation - PlayerScreenLocation).GetSafeNormal();
	}
}

void APC_PlayerCharacter::OnTouchEnd(ETouchIndex::Type TouchIndex, FVector TouchLocation)
{
	CurrentLocation = FVector2D::ZeroVector;
	MoveDirection = FVector2D::ZeroVector;
	PlayerScreenLocation = FVector2D::ZeroVector;
}
