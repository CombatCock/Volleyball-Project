// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "VolleyballGameState.generated.h"

/**
 * 
 */
UCLASS()
class VOLLEYBALL_API AVolleyballGameState : public AGameState
{
	GENERATED_BODY()
	
public:

	AVolleyballGameState();

	void UpdatePlayerLists();


private:
	UPROPERTY(ReplicatedUsing = UpdatePlayerWidget)
	TArray<TObjectPtr<APlayerState>> AllPlayerStates;
	
	UFUNCTION()
	virtual void UpdatePlayerWidget();

	UFUNCTION(Server, Reliable)
	void Server_UpdatePlayerWidget();

};
