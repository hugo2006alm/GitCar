// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Signal.h"
#include "Traffic_Lights.generated.h"

class UStaticMeshComponent;
class USpotLightComponent;
class UBoxComponent;

UCLASS()
class GITCAR_API ATraffic_Lights : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Traffic Light", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Traffic Light", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpotLightComponent> RedLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Traffic Light", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpotLightComponent> YellowLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Traffic Light", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpotLightComponent> GreenLight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Traffic Light", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> CollisionBox;

public:	
	// Sets default values for this actor's properties
	ATraffic_Lights();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void StartChangeSignal();
	void ChangeToRedLight();
	void ChangeToYellowLight();
	void ChangeToGreenLight();

	void SetSignalValue(ESignal NewSignal) { SignalValue = NewSignal; OnChange(SignalValue); };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Light")
	float ChangeTime = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Light")
	float ChangeDelay = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Traffic Light")
	bool StartsGreen = true;

	TObjectPtr<class AAI_Car> OverlappedCar;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(Category = "Traffic Light")
	void OnChange(ESignal NewSignal);

	UFUNCTION(Category = "Traffic Light")
	void OnTrafficLightOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	ESignal SignalValue;
};
