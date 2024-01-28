// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SplineComponent.h>
#include "Path.generated.h"

UCLASS()
class GITCAR_API APath : public AActor
{
	GENERATED_BODY()
	
	TObjectPtr<USplineComponent> Spline;

public:	

	APath();
};
