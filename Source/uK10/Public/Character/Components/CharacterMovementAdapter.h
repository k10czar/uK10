// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterMovementAdapter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UK10_API UCharacterMovementAdapter : public UActorComponent
{
	GENERATED_BODY()

private:
	float _startTime;
	void TrySetCharacterMovementData();

public:	
	// Sets default values for this component's properties
	UCharacterMovementAdapter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	float GetTimeSinceStart();

	void MoveForward( float value );
	void MoveRight( float value );
};
