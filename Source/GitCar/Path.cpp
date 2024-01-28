// Fill out your copyright notice in the Description page of Project Settings.


#include "Path.h"

// Sets default values
APath::APath()
{
	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
}

