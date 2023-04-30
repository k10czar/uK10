// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/CharacterMovementAdapter.h"
#include "K10CharacterBase.generated.h"

UCLASS()
class UK10_API AK10CharacterBase : public ACharacter
{
	GENERATED_BODY()

private:
	float _startTime;

public:
	// Sets default values for this character's properties
	AK10CharacterBase();

protected:
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom Components", meta = (AllowPrivateAccess = "true"))
	UCharacterMovementAdapter* _movementAdapter;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	/** Returns time since Start **/
	// FORCEINLINE float GetTimeSinceStart() const { return _timeCounter; }
	float GetTimeSinceStart();
	
	FORCEINLINE UCharacterMovementAdapter* GetMovementAdapter() const { return _movementAdapter; }
};