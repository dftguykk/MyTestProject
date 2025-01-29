// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Drone.h"
#include "Tower.h"
#include "MyPlayerController.h"

void AMyGameModeBase::ActorDied(AActor* DeadActor)
{
	if (DeadActor == Drone)
	{
		Drone->HandleDestruction();
		if (MyPlayerController)
		{
			MyPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);

	}
	else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
	{
		DestroyedTower->HandleDestruction();
		--TargetTowers;
		if (TargetTowers == 0)
		{
			GameOver(true);
		}
	}
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();

}

void AMyGameModeBase::HandleGameStart()
{
	TargetTowers = GetTargetTowerCount();
	Drone = Cast<ADrone>(UGameplayStatics::GetPlayerPawn(this, 0));
	MyPlayerController = Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	
	if (MyPlayerController)
	{
		MyPlayerController->SetPlayerEnabledState(false);

		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(MyPlayerController, &AMyPlayerController::SetPlayerEnabledState, true);
		GetWorldTimerManager().SetTimer(PlayerEnableTimerHandle, PlayerEnableTimerDelegate, StartDelay, false);
	}
}

int32 AMyGameModeBase::GetTargetTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}