// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Car_UI.h"

void UAI_Car_UI::UpdateSpeed(float NewSpeed)
{
	float FormattedSpeed = FMath::Abs(NewSpeed) * (bIsMPH ? 0.022f : 0.036f);

	OnSpeedUpdate(FormattedSpeed);
}