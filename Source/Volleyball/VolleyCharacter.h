// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "VolleyCharacter.generated.h"

//Classes
class UInputAction;
class UInputMappingContext;

//Structs
struct FInputActionInstance;

UCLASS()
class VOLLEYBALL_API AVolleyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AVolleyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* MoveInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* JumpInputAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	UInputAction* DashInputAction;

	void Moving(const FInputActionInstance& Instance);
	void Jumping(const FInputActionInstance& Instance);
	void Dashing(const FInputActionInstance& Instance);

};
