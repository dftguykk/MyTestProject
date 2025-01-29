// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"


ADrone::ADrone()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ADrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Forward/Backward"), this, &ADrone::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn Right/Left"), this, &ADrone::Turn);
	PlayerInputComponent->BindAxis(TEXT("Rotate"), this, &ADrone::RotateInPlace);
	PlayerInputComponent->BindAxis(TEXT("Up/Down"), this, &ADrone::UpDown);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ADrone::Fire);
}

void ADrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DronePlayerController)
	{
		FHitResult HitResult;
		DronePlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

		RotateTurret(HitResult.ImpactPoint);

	}
}

void ADrone::HandleDestruction()
{
	Super::HandleDestruction();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ADrone::BeginPlay()
{
	Super::BeginPlay();

	DronePlayerController = Cast<APlayerController>(GetController());

}

void ADrone::Move(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void ADrone::Turn(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.Y = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void ADrone::RotateInPlace(float Value)
{
	FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * RotateRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);

	UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value);
	UE_LOG(LogTemp, Warning, TEXT("RotateRate: %f"), RotateRate);
}

void ADrone::UpDown(float Value)
{
	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.Z = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}