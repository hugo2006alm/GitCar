// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GitCarPawn.h"
#include "GitCarSportsCar.generated.h"

/**
 *  Sports car wheeled vehicle implementation
 */
UCLASS(abstract)
class GITCAR_API AGitCarSportsCar : public AGitCarPawn
{
	GENERATED_BODY()
	
public:

	AGitCarSportsCar();
};
