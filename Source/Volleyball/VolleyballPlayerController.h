// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "VolleyballPlayerController.generated.h"


//Classes
class UInputAction;
class UInputMappingContext;

//Structs
struct FInputActionInstance;

/**
 * 
 */
UCLASS()
class VOLLEYBALL_API AVolleyballPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Server, Reliable)
	void SR_SpawnPlayer();

	UFUNCTION(Client, Reliable)
	void OC_KickPlayer();

	UFUNCTION()
	void SpawnBall();

protected:
	virtual void BeginPlay() override;

private:
	virtual void SetupInputComponent() override;

	void BindInputMappingContext();

	bool GetPlayerHUD();

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputMappingContext* MappingContext; 

	UPROPERTY()
	class AVolleyballHUD* PlayerHUD;

	//InputAction Functions:
	void RespawnPlayer(const FInputActionInstance& Instance);
	void BallRespawn();
	void ToggleInventory();
	void ToggleMountsMenu();
	void TogglePlayerList();

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SpawnInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ToggleInventoryInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* ToggleMountsMenuInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* TogglePlayerListInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* SpawnBallInputAction;

};
