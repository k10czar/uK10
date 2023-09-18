// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "K10PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UK10_API AK10PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AK10PlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float _baseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float _baseLookUpRate;

	virtual void SetupInputComponent() override;
	virtual void OnPossess( class APawn* inPawn ) override;
	virtual void OnUnPossess() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input")
    class UInputMappingContext* _inputMapping;

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    class UInputAction* _moveAction;
 
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    class UInputAction* _lookAction;

private:
    class APawn* _pawn;
    class ACharacter* _character;
    class AK10CharacterBase* _k10Char;
    class UCharacterMovementComponent* _movement;
    class UCharacterMovementAdapter* _movementAdapter;

public:
	void Crouch();
	void StopCrouch();
	void Jump();
	void StopJumping();
	void AddControllerYawInput( float value );
	void AddControllerPitchInput( float value );
	void TurnAtRate(float rate);
	void LookUpAtRate(float rate);
	void MoveForward(float value);
	void MoveRight(float value);
	void Move( const FInputActionValue& value );
	void Look( const FInputActionValue& Value);
};