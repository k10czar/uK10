// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "K10InputManager.generated.h"

/**
 * 
 */
UCLASS()
class UK10InputManager : public UObject
{
	GENERATED_BODY()
	
public:
    UFUNCTION(BlueprintCallable)
    static UK10InputManager* GetInstance();

    // static void SetWidget( UUserWidget* widget );
    static void TeardownWidgets();

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    class UInputMappingContext* InputMapping;

private:
    static UK10InputManager* _instance;
};
