// Fill out your copyright notice in the Description page of Project Settings.


#include "VolleyballHUD.h"
#include "Blueprint/UserWidget.h"

void AVolleyballHUD::BeginPlay()
{
    Super::BeginPlay();

    OwningPlayerController = GetOwningPlayerController();
    
}

void AVolleyballHUD::ToggleWidget(UUserWidget* TargetWidget)
{
    if (!TargetWidget) return;

    WidgetToFocus = TargetWidget;

    for (UUserWidget* Widget : GameWidgetList)
    {
        if (!Widget) return;

        if (Widget == WidgetToFocus)
        {
            if (WidgetToFocus->IsVisible())
            {
                FocusGame();
            }
            else
            {
                FocusWidget();
            }
        }
        else
        {
            if (Widget->IsVisible())
            {
                Widget->SetVisibility(ESlateVisibility::Collapsed);
            }
        }
    }
}

void AVolleyballHUD::FocusGame()
{
    WidgetToFocus->SetVisibility(ESlateVisibility::Collapsed);
    OwningPlayerController->SetInputMode(FInputModeGameOnly());
    OwningPlayerController->bShowMouseCursor = false;
}

void AVolleyballHUD::FocusWidget()
{
    WidgetToFocus->SetVisibility(ESlateVisibility::Visible);
    FInputModeGameAndUI InputData;
    InputData.SetWidgetToFocus(WidgetToFocus->TakeWidget());
    OwningPlayerController->SetInputMode(InputData);
    OwningPlayerController->bShowMouseCursor = true;
}
