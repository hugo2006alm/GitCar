// Fill out your copyright notice in the Description page of Project Settings.

#include "Traffic_Lights.h"
#include "Components/SpotLightComponent.h"
#include "Components/BoxComponent.h"
#include "ChaosVehicleMovementComponent.h"
#include "AI_Car.h"

// Sets default values
ATraffic_Lights::ATraffic_Lights()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	RedLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Red Light"));
	RedLight->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	RedLight->SetRelativeLocation(FVector(0, 0, 0));
	RedLight->SetIntensityUnits(ELightUnits::EV);
	RedLight->SetIntensity(0);
	RedLight->SetSourceRadius(25);
	RedLight->SetLightColor(FLinearColor(255, 0, 0));

	YellowLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Yellow Light"));
	YellowLight->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	YellowLight->SetRelativeLocation(FVector(0, 0, 0));
	YellowLight->SetIntensityUnits(ELightUnits::EV);
	YellowLight->SetIntensity(0);
	YellowLight->SetSourceRadius(25);
	YellowLight->SetLightColor(FLinearColor(255, 255, 0));

	GreenLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("Green Light"));
	GreenLight->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	GreenLight->SetRelativeLocation(FVector(0, 0, 0));
	GreenLight->SetIntensityUnits(ELightUnits::EV);
	GreenLight->SetIntensity(0);
	GreenLight->SetSourceRadius(25);
	GreenLight->SetLightColor(FLinearColor(0, 255, 0));

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	CollisionBox->AttachToComponent(Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionBox->SetRelativeLocation(FVector(0, 0, 0));
	CollisionBox->InitBoxExtent(FVector(100, 100, 100));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATraffic_Lights::OnTrafficLightOverlapBegin);
}

// Called when the game starts or when spawned
void ATraffic_Lights::BeginPlay()
{
	Super::BeginPlay();

	SignalValue = StartsGreen ? ESignal::Green : ESignal::Red;
	StartChangeSignal();
}

// Called every frames
void ATraffic_Lights::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATraffic_Lights::StartChangeSignal() {
	if (SignalValue == ESignal::Green) {
		ChangeToRedLight();
	}
	else if (SignalValue == ESignal::Red) {
		ChangeToGreenLight();
	}
}

void ATraffic_Lights::ChangeToRedLight() {
	RedLight->SetIntensity(32);
	YellowLight->SetIntensity(0);
	GreenLight->SetIntensity(0);

	SetSignalValue(ESignal::Red);

	// Set a timer to change back to the red light after 10 seconds
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATraffic_Lights::ChangeToYellowLight, 10.0f, false);
}

void ATraffic_Lights::ChangeToYellowLight() {
	RedLight->SetIntensity(0);
	YellowLight->SetIntensity(32);
	GreenLight->SetIntensity(0);


	// Set a timer to change back to the red light after 10 seconds
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, SignalValue == ESignal::Green ? &ATraffic_Lights::ChangeToRedLight : &ATraffic_Lights::ChangeToGreenLight, 1.0f, false);
	SetSignalValue(ESignal::Yellow);
}

void ATraffic_Lights::ChangeToGreenLight() {
	RedLight->SetIntensity(0);
	YellowLight->SetIntensity(0);
	GreenLight->SetIntensity(32);

	SetSignalValue(ESignal::Green);

	// Set a timer to change back to the red light after 10 seconds
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATraffic_Lights::ChangeToYellowLight, 10.0f, false);
}

void ATraffic_Lights::OnTrafficLightOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	OverlappedCar = Cast<AAI_Car>(OtherActor);
	if (OverlappedCar)
	{
		if (SignalValue == ESignal::Red)
		{
			OverlappedCar->GetVehicleMovement()->SetThrottleInput(0.0f);
			OverlappedCar->GetVehicleMovement()->SetBrakeInput(1.0f);
			OverlappedCar->GetVehicleMovement()->SetTargetGear(0, true);
			OverlappedCar->SetTrafficStopped(true);
		}
	}
}

void ATraffic_Lights::OnChange(ESignal NewSignal) {
	if (OverlappedCar) {
		if (SignalValue == ESignal::Green && OverlappedCar->GetTrafficStopped()) {
			OverlappedCar->GetVehicleMovement()->SetBrakeInput(0.0f);
			OverlappedCar->GetVehicleMovement()->SetTargetGear(1, true);
			OverlappedCar->GetVehicleMovement()->SetThrottleInput(1.0f);
		}
	}
}
