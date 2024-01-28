// Copyright Epic Games, Inc. All Rights Reserved.

#include "GitCarWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UGitCarWheelRear::UGitCarWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}