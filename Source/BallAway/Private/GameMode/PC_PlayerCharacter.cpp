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

void APC_PlayerCharacter::Tick(float DeltaTime)
{
	// �÷��̾��� ��ġ (������ǥ)�� ��ũ�� ��ǥ�� �ٲ�
	ProjectWorldLocationToScreen(BAPlayer->GetActorLocation(), PlayerScreenLocation);

	BALOG(Warning, TEXT("Touch : %f, Player : %f"), CurrentLocation.X, PlayerScreenLocation.X);
	BALOG(Error, TEXT("MoveDirection.X : %f"), FMath::Abs(CurrentLocation.X - PlayerScreenLocation.X));

	if (FMath::Abs(CurrentLocation.X - PlayerScreenLocation.X) > 10.f)
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
	else
	{
		//BALOG(Error, TEXT("asdf"));
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
	// ù ��ġ ��ġ
	CurrentLocation = (FVector2D)TouchLocation;

	ProjectWorldLocationToScreen(BAPlayer->GetActorLocation(), PlayerScreenLocation);
}

void APC_PlayerCharacter::OnTouchTick(ETouchIndex::Type TouchIndex, FVector TouchLocation)
{

	// ���� ��ġ ��ġ
	CurrentLocation = (FVector2D)TouchLocation;


	// ���� ���������� ���� (��, ��)
	MoveDirection = (CurrentLocation - PlayerScreenLocation).GetSafeNormal();

}

void APC_PlayerCharacter::OnTouchEnd(ETouchIndex::Type TouchIndex, FVector TouchLocation)
{
	//FirstLocation = FVector2D::ZeroVector;
	CurrentLocation = FVector2D::ZeroVector;
	MoveDirection = FVector2D::ZeroVector;
	PlayerScreenLocation = FVector2D::ZeroVector;
}
