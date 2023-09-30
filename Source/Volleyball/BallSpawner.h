// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "BallSpawner.generated.h"

/**
 * 
 */
UCLASS()
class VOLLEYBALL_API ABallSpawner : public ATargetPoint
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

	UFUNCTION(Client, Reliable)
	void SR_SpawnBall();	

private:
	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<class ABallBase> Ball;

	UPROPERTY(EditAnywhere, Category = "Spawn")
	float Impulse = 50;

	void LaunchBall(UStaticMeshComponent* Mesh);
	void FreezeBall(UStaticMeshComponent* Mesh);
	void UnfreezeBall(UStaticMeshComponent* Mesh);
	
};
