// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "Tower.generated.h"

/**
 *
 */
UCLASS()
class MYTESTPROJECT_API ATower : public ABaseCharacter
{
	GENERATED_BODY()


public:

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:

	virtual void BeginPlay() override;

private:

	class ADrone* Drone;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 300.f;

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f;
	void CheckFireCondition();

	bool InFireRange();
};
