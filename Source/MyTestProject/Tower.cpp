// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Drone.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (InFireRange())
	{
		RotateTurret(Drone->GetActorLocation());
	}
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Drone = Cast<ADrone>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true);
}

void ATower::CheckFireCondition()
{
	if (InFireRange())
	{
		Fire();
	}
}

bool ATower::InFireRange()
{
	if (Drone)
	{
		float Distance = FVector::Dist(GetActorLocation(), Drone->GetActorLocation());
		if (Distance <= FireRange)
		{
			return true;
		}
	}

	return false;
}
