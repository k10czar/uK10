// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Character/CharacterMovementAdapter.h"
#include "Character/Components/ActorCameraComponent.h"
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

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float _baseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float _baseLookUpRate;

protected:
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom Components", meta = (AllowPrivateAccess = "true"))
	UCharacterMovementAdapter* _movementAdapter;
	
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom Components", meta = (AllowPrivateAccess = "true"))
	UActorCameraComponent* _actorCameraComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);
	
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/** Returns time since Start **/
	// FORCEINLINE float GetTimeSinceStart() const { return _timeCounter; }
	float GetTimeSinceStart();
};