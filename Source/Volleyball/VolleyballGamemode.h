// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "VolleyballGamemode.generated.h"

/**
 * 
 */
UCLASS()
class VOLLEYBALL_API AVolleyballGamemode : public AGameMode
{
	GENERATED_BODY()

public:
	//overrides from AGameMode
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void Logout(AController* Exiting) override;
	virtual void SwapPlayerControllers(APlayerController* OldPC, APlayerController* NewPC);

	void SpawnPlayer(APlayerController* PlayerControler);
	void SpawnBall();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TArray<APlayerController*> ConnectedPlayers;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AVolleyCharacter> PlayerCharacter;

	FTransform FindRandomPlayerStart() const;

	UFUNCTION()
	void UpdatePlayerList();

	UFUNCTION(BlueprintCallable)
	void KickPlayer(int32 PlayerID);

};
