// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickUp.generated.h"

class USphereComponent;

UCLASS()
class MYTESTPROJECT_API ABasePickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePickUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "PickUp")
	USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "PickUp")
	float RespawnTime = 5.0f;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	virtual bool GivePickUpTo(APawn* PlayerPawn);

	void PickUpWasTaken();
	void Respawn();
};
