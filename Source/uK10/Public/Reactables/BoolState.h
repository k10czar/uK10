// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BoolState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FBoolStateChange, bool, newValue );

UCLASS(Blueprintable)
class UBoolState : public UObject
{
	GENERATED_BODY()
	
public:
    UPROPERTY(BlueprintAssignable, Category = "EventDispatchers")
    FBoolStateChange OnStateChange;
	
    bool GetState();
    void SetState( bool newValue );

    void SetTrue();
    void SetFalse();
    void Toggle();

private:
    bool _value;
};
