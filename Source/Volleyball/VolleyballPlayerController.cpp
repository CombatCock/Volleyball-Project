// Fill out your copyright notice in the Description page of Project Settings.


#include "VolleyballPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "VolleyballGamemode.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputAction.h"
#include "VolleyballHUD.h"


void AVolleyballPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (!IsLocalPlayerController()) return;

    SR_SpawnPlayer();
    BindInputMappingContext();
    if (!GetPlayerHUD())
    {
        UE_LOG(LogTemp, Warning, TEXT("No HUD Class Found"));
    }
}


//Функция вызываемая на сервере. В дополнение к названию функции идёт _Implementation
void AVolleyballPlayerController::SR_SpawnPlayer_Implementation()
{
    AVolleyballGamemode* CurrentGamemode = Cast<AVolleyballGamemode>(UGameplayStatics::GetGameMode(this));
    if (!CurrentGamemode) return;
    CurrentGamemode->SpawnPlayer(this);
}

//Использовать, если в UFUNCTION стоит WithValidation. В дополнение к названию функции идёт _Validate
// bool AVolleyballPlayerController::SR_SpawnPlayer_Validate()
// {
//     return true;
// }

void AVolleyballPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
    if (!Input) return;
    Input->BindAction(SpawnInputAction, ETriggerEvent::Triggered, this, &AVolleyballPlayerController::RespawnPlayer);
    Input->BindAction(ToggleInventoryInputAction, ETriggerEvent::Triggered, this, &AVolleyballPlayerController::ToggleInventory);
    Input->BindAction(ToggleMountsMenuInputAction, ETriggerEvent::Triggered, this, &AVolleyballPlayerController::ToggleMountsMenu);
    Input->BindAction(TogglePlayerListInputAction, ETriggerEvent::Triggered, this, &AVolleyballPlayerController::TogglePlayerList);
    Input->BindAction(SpawnBallInputAction, ETriggerEvent::Triggered, this, &AVolleyballPlayerController::SpawnBall);
}

void AVolleyballPlayerController::BindInputMappingContext()
{
    if (!MappingContext) return;
    if (ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(Player))
    {
        if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            InputSystem->ClearAllMappings();
            InputSystem->AddMappingContext(MappingContext, 0);
        }
    }
}

bool AVolleyballPlayerController::GetPlayerHUD()
{
    PlayerHUD = Cast<AVolleyballHUD>(GetHUD());
    if (PlayerHUD)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void AVolleyballPlayerController::RespawnPlayer(const FInputActionInstance &Instance)
{
    SR_SpawnPlayer();
}

void AVolleyballPlayerController::ToggleInventory()
{
    PlayerHUD->ToggleInventory();
}

void AVolleyballPlayerController::ToggleMountsMenu()
{
    PlayerHUD->ToggleMounts();
}

void AVolleyballPlayerController::TogglePlayerList()
{
    PlayerHUD->TogglePlayerList();
}

void AVolleyballPlayerController::OC_KickPlayer_Implementation()
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
    UE_LOG(LogTemp, Warning, TEXT("You were kicked!"));
}

void AVolleyballPlayerController::BallRespawn()
{
    SpawnBall();
}

void AVolleyballPlayerController::SpawnBall()
{
    AVolleyballGamemode* CurrentGamemode = Cast<AVolleyballGamemode>(UGameplayStatics::GetGameMode(this));
    if (!CurrentGamemode) return;
    CurrentGamemode->SpawnBall();
}

