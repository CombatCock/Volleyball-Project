// Fill out your copyright notice in the Description page of Project Settings.


#include "VolleyballGameState.h"
#include "VolleyballPlayerState.h"
#include "Net/UnrealNetwork.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "PlayerList.h"

AVolleyballGameState::AVolleyballGameState()
{
    bReplicates = true;
}

void AVolleyballGameState::UpdatePlayerLists()
{
    AllPlayerStates = PlayerArray;
    Server_UpdatePlayerWidget();
    
    MARK_PROPERTY_DIRTY_FROM_NAME(AVolleyballGameState, AllPlayerStates, this);
}

void AVolleyballGameState::UpdatePlayerWidget()
{
    TArray<UUserWidget*> FoundWidgets;
    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundWidgets, UPlayerList::StaticClass(), false);
    for (UUserWidget* Widget : FoundWidgets)
    {
        Cast<UPlayerList>(Widget)->UpdateWidget();
    }
}

void AVolleyballGameState::Server_UpdatePlayerWidget_Implementation()
{
    UpdatePlayerWidget();
}

void AVolleyballGameState::GetLifetimeReplicatedProps( TArray<FLifetimeProperty> & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    FDoRepLifetimeParams SharedParams;
    SharedParams.bIsPushBased = true;
    DOREPLIFETIME_WITH_PARAMS_FAST(AVolleyballGameState, AllPlayerStates, SharedParams);

}

