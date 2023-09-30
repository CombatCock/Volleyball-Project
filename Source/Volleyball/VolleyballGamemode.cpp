// Fill out your copyright notice in the Description page of Project Settings.


#include "VolleyballGamemode.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/KismetMathLibrary.h"
#include "VolleyCharacter.h"
#include "VolleyballGameState.h"
#include "VolleyballPlayerController.h"
#include "Engine/World.h"
#include "BallSpawner.h"


void AVolleyballGamemode::BeginPlay()
{
    Super::BeginPlay();
    
}

FTransform AVolleyballGamemode::FindRandomPlayerStart() const
{
    TArray<AActor*> PlayerStartArray;
    UGameplayStatics::GetAllActorsOfClass(this, APlayerStart::StaticClass(), PlayerStartArray);
    int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0, PlayerStartArray.Num()-1);
    return PlayerStartArray[RandomIndex]->GetActorTransform();
}


void AVolleyballGamemode::SpawnPlayer(APlayerController* PlayerControler)
{
    APawn* PlayerPawn = PlayerControler->GetPawn();
    if (PlayerPawn)
    {
        PlayerPawn->Destroy();
    }
    FTransform PlayerSpawnLocation = FindRandomPlayerStart();

    PlayerPawn = GetWorld()->SpawnActor<AVolleyCharacter>(PlayerCharacter, PlayerSpawnLocation);
    if (!PlayerPawn) return;
    PlayerControler->Possess(PlayerPawn);
}

void AVolleyballGamemode::SpawnBall()
{
    ABallSpawner* BallSpawner = Cast<ABallSpawner>(UGameplayStatics::GetActorOfClass(this, ABallSpawner::StaticClass()));
    if (BallSpawner)
    {
        BallSpawner->SR_SpawnBall();
    }
}

//�������� ������ ���� �������������� ������� (�� PC) � ������ � ������
//����� ������� ��� ����������� ������ ������
void AVolleyballGamemode::PostLogin(APlayerController *NewPlayer)
{
    Super::PostLogin(NewPlayer);

    ConnectedPlayers.Add(NewPlayer);
    UpdatePlayerList();
    
}

//������� �������������� ������ �� ������
//����� ������� ��� ���������� ������
void AVolleyballGamemode::Logout(AController *Exiting)
{
    APlayerController* DisconnectedPlayer = Cast<APlayerController>(Exiting);
    if (!DisconnectedPlayer) return;
    ConnectedPlayers.Remove(DisconnectedPlayer);
    UpdatePlayerList();
}


//����� ������� ��� ����� PC � ������ (�������� ��� �������� �� ���� ����� � ��� ����)
void AVolleyballGamemode::SwapPlayerControllers(APlayerController *OldPC, APlayerController *NewPC)
{
    ConnectedPlayers.Add(NewPC);
    UpdatePlayerList();
}

void AVolleyballGamemode::UpdatePlayerList()
{
    AVolleyballGameState* VolleyGameState = Cast<AVolleyballGameState>(UGameplayStatics::GetGameState(GetWorld()));
    VolleyGameState->UpdatePlayerLists();
}

void AVolleyballGamemode::KickPlayer(int32 PlayerID)
{
    Cast<AVolleyballPlayerController>(ConnectedPlayers[PlayerID])->OC_KickPlayer();
}
