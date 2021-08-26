// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(BallAway, Log, All);

#define BA_CALLINFO (FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")"))

#define BA_S(Verbosity) UE_LOG(BallAway, Verbosity, TEXT("%s"), *BA_CALLINFO)

#define BALOG(Verbosity,Format, ...) UE_LOG(BallAway, Verbosity, TEXT("%s %s"), *BA_CALLINFO, *FString::Printf(Format, ##__VA_ARGS__))

//GSCHECK 매크로를 추가 : 런타임에서 문제가 발생할 때 붉은색 에러로그 뿌리고 함수 반환
#define BACHECK(Expr, ...){if(!(Expr)) {BALOG(Error, TEXT("ASSERTION : %s"), TEXT("'"#Expr"'")); return __VA_ARGS__;}}


