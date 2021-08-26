// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(BallAway, Log, All);

#define BA_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

#define BA_S(Verbosity) UE_LOG(BallAway, Verbosity, TEXT("%s"), *BA_CALLINFO)

#define BALOG(Verbosity,Format, ...) UE_LOG(BallAway, Verbosity, TEXT("%s %s"), *BA_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

//GSCHECK ��ũ�θ� �߰� : ��Ÿ�ӿ��� ������ �߻��� �� ������ �����α� �Ѹ��� �Լ� ��ȯ
#define BACHECK(Expr, ...){if(!(Expr)) {BALOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}


