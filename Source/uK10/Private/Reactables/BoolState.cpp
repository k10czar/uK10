// Fill out your copyright notice in the Description page of Project Settings.


#include "Reactables/BoolState.h"

bool UBoolState::GetState() { return _value; }

void UBoolState::SetState(bool newValue)
{
    if( _value == newValue ) return;

    _value = newValue;
    OnStateChange.Broadcast( _value );
    UE_LOG( LogTemp, Display, TEXT( "BoolState changed to %s" ), (_value ? TEXT("true") : TEXT("false") ) )
}

void UBoolState::SetTrue() { SetState( true ); }
void UBoolState::SetFalse() { SetState( false ); }
void UBoolState::Toggle() { SetState( !_value ); }

