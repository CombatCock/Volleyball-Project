// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "VolleyballHUD.generated.h"

/**
 * 
 */
UCLASS()
class VOLLEYBALL_API AVolleyballHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintImplementableEvent)
	void ToggleInventory();

	UFUNCTION(BlueprintImplementableEvent)
	void ToggleMounts();

	UFUNCTION(BlueprintImplementableEvent)
	void TogglePlayerList();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UUserWidget* WidgetToFocus;

	UPROPERTY(BlueprintReadWrite)
	TArray<UUserWidget*> GameWidgetList;

private:
	UFUNCTION(BlueprintCallable)
	void ToggleWidget(UUserWidget* TargetWidget);

	void FocusGame();
	void FocusWidget();

	APlayerController* OwningPlayerController;



};
