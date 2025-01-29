// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUp.h"
#include "HealthComponent.h"
#include "../../Intermediate/ProjectFiles/Utils.h"

bool AHealthPickUp::GivePickUpTo(APawn* PlayerPawn)
{
	const auto HealthComponent = Utils::GetPlayerComponent<UHealthComponent>(PlayerPawn);
	if (!HealthComponent) return false;

	return HealthComponent->TryToAddHealth(HealthAmount);
}