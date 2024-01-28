// Copyright Epic Games, Inc. All Rights Reserved.

#include "GitCarWheelFront.h"
#include "UObject/ConstructorHelpers.h"

UGitCarWheelFront::UGitCarWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}