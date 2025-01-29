// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePickUp.h"
#include "HealthPickUp.generated.h"

/**
 * 
 */
UCLASS()
class MYTESTPROJECT_API AHealthPickUp : public ABasePickUp
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PickUp", meta = (ClampMin = "1.0", ClampMax = "100.0"))
	float HealthAmount = 50.0f;

private:
	virtual bool GivePickUpTo(APawn* PlayerPawn) override;
};
