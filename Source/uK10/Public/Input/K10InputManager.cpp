// Fill out your copyright notice in the Description page of Project Settings.


#include "K10InputManager.h"


UK10InputManager* UK10InputManager::_instance = nullptr;

UK10InputManager* UK10InputManager::GetInstance()
{
    if( _instance == nullptr )
    {
        _instance = NewObject<UK10InputManager>();
    }

    return _instance;
}