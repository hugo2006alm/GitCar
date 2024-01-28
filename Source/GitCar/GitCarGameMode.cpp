// Copyright Epic Games, Inc. All Rights Reserved.

#include "GitCarGameMode.h"
#include "GitCarPlayerController.h"

AGitCarGameMode::AGitCarGameMode()
{
	PlayerControllerClass = AGitCarPlayerController::StaticClass();
}
