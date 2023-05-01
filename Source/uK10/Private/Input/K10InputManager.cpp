// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/K10InputManager.h"
#include "Log/K10Macros.h"
#include "Blueprint/UserWidget.h"
#include "UObject/Object.h"


UK10InputManager* UK10InputManager::_instance = nullptr;

UK10InputManager* UK10InputManager::GetInstance()
{
    if( _instance == nullptr )
    {
        _instance = NewObject<UK10InputManager>();
    }

    return _instance;
}

void UK10InputManager::SetWidget( UUserWidget* widget )
{
	UE_LOG(LogTemp, Warning, TEXT("UK10InputManager::SetWidget( %s )"), *widget->GetFullName() );
	// this->AddToViewport();

	// UWorld* World = UObject::GetWorld();
	// if (!ensure(World != nullptr)) return;

	// APlayerController* PlayerController = World->GetFirstPlayerController();
	// if (!ensure(PlayerController != nullptr)) return;

	// FInputModeUIOnly InputModeData;
	// InputModeData.SetWidgetToFocus( widget->TakeWidget() );
	// InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

	// PlayerController->SetInputMode(InputModeData);

	// PlayerController->bShowMouseCursor = true;
}

void UK10InputManager::TeardownWidgets()
{
	UE_LOG(LogTemp, Warning, TEXT("UK10InputManager::TeardownWidgets()") );
	// this->RemoveFromViewport();

	// UWorld* World = UObject::GetWorld();
	// if (!ensure(World != nullptr)) return;

	// APlayerController* PlayerController = World->GetFirstPlayerController();
	// if (!ensure(PlayerController != nullptr)) return;

	// FInputModeGameOnly InputModeData;
	// PlayerController->SetInputMode(InputModeData);

	// PlayerController->bShowMouseCursor = false;
}