// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Path.h"
#include "AI_Car.generated.h"

/**
 * 
 */
UCLASS()
class GITCAR_API AAI_Car : public AWheeledVehiclePawn
{
	GENERATED_BODY()
	
protected:

	AAI_Car();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	TObjectPtr<APath> ActivePath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float MaxThrottleInput = 0.5f;

	float CurrentThrottleInput = 0;

	bool TrafficStopped = false;

public:

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "AI")
	float GetPath();

	bool GetTrafficStopped() const { return TrafficStopped; };
	void SetTrafficStopped(bool New) { TrafficStopped = New; };

	float GetMaxThrottleInput() const { return MaxThrottleInput; };
};
