// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Car.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
#include "ChaosWheeledVehicleMovementComponent.h"
#include <Components/SplineComponent.h>
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


AAI_Car::AAI_Car() {
    //Create our components
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootSceneComponent"));
    SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

    //Attach our components
    SpringArmComp->SetupAttachment(GetMesh());
    CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

    //Assign SpringArm class variables.
    SpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-30.0f, 0.0f, 0.0f));
    SpringArmComp->TargetArmLength = 400.f;
    SpringArmComp->bEnableCameraLag = true;
    SpringArmComp->CameraLagSpeed = 3.0f;
}

float AAI_Car::GetPath()
{
    USplineComponent* Spline = ActivePath->GetComponentByClass<USplineComponent>();
    FVector ActorLocation = GetActorLocation();

    FVector NextLocation = (Spline->FindTangentClosestToWorldLocation(ActorLocation, ESplineCoordinateSpace::World)) + ActorLocation;
    FRotator FinalRotation = UKismetMathLibrary::NormalizedDeltaRotator(UKismetMathLibrary::FindLookAtRotation(ActorLocation, Spline->FindLocationClosestToWorldLocation(NextLocation, ESplineCoordinateSpace::World)), GetActorRotation());

    return UKismetMathLibrary::MapRangeClamped(FinalRotation.Yaw, -90.0f, 90.0f, -1.0f, 1.0f);
}

void AAI_Car::BeginPlay()
{
    Super::BeginPlay();

    GetVehicleMovement()->SetUseAutomaticGears(false);
    GetVehicleMovement()->SetTargetGear(1, true);
    GetVehicleMovement()->SetThrottleInput(MaxThrottleInput);
    CurrentThrottleInput = GetVehicleMovement()->GetThrottleInput();
}

void AAI_Car::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    GetVehicleMovement()->SetSteeringInput(GetPath());
    CurrentThrottleInput = GetVehicleMovement()->GetThrottleInput();
}
