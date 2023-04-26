// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "K10CharacterMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UK10_API UK10CharacterMovementComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	float _startTime;

public:	
	// Sets default values for this component's properties
	UK10CharacterMovementComponent();

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
