// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Drone.generated.h"

/**
 *
 */
UCLASS()
class MYTESTPROJECT_API ADrone : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ADrone();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

	APlayerController* GetDronePlayerController() const { return DronePlayerController; };

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float RotateRate = 45.f;

	void Move(float Value);
	void Turn(float Value);
	void RotateInPlace(float Value);
	void UpDown(float Value);

	APlayerController* DronePlayerController;
};