// Fill out your copyright notice in the Description page of Project Settings.


#include "VolleyCharacter.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"

// Sets default values
AVolleyCharacter::AVolleyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

//Called when the game starts or when spawned
void AVolleyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVolleyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVolleyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent))
	{
		Input->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &AVolleyCharacter::Moving);
		Input->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		Input->BindAction(DashInputAction, ETriggerEvent::Triggered, this, &AVolleyCharacter::Dashing);
	}

}

void AVolleyCharacter::Moving(const FInputActionInstance& Instance)
{
	const float MovementVector = Instance.GetValue().Get<float>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);
	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	FVector Right = GetActorForwardVector();
	AddMovementInput(ForwardDirection, MovementVector);
}

void AVolleyCharacter::Dashing(const FInputActionInstance& Instance)
{
}
