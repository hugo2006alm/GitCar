// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AI_CarPlayerController.generated.h"

class UInputMappingContext;
class AAI_Car;
class AI_Car_UI;

/**
 * 
 */
UCLASS()
class GITCAR_API AAI_CarPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* InputMappingContext;

	/** Pointer to the controlled vehicle pawn */
	TObjectPtr<AAI_Car> VehiclePawn;

	/** Type of the UI to spawn */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = UI)
	TSubclassOf<AI_Car_UI> VehicleUIClass;

	/** Pointer to the UI widget */
	TObjectPtr<AI_Car_UI> VehicleUI;

protected:

	virtual void BeginPlay() override;

public:

	virtual void Tick(float Delta) override;

protected:

	virtual void OnPossess(APawn* InPawn) override;

};
