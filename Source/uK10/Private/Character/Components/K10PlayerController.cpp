// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/K10PlayerController.h"
#include "Character/K10CharacterBase.h"
#include "Character/Components/CharacterMovementAdapter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "Log/K10Macros.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"


AK10PlayerController::AK10PlayerController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("AK10PlayerController::ctor()"));
	_baseTurnRate = 45.f;
	_baseLookUpRate = 45.f;
}


void AK10PlayerController::OnPossess( class APawn* inPawn )
{
	UE_LOG( LogTemp, Warning, TEXT("AK10PlayerController::OnPossess( %s )"), ( inPawn != nullptr ) ?  *inPawn->GetClass()->GetName() : TEXT( "NULL" ) );
	Super::OnPossess( inPawn );
    _pawn = inPawn;
    if( _pawn == nullptr ) return;
    _character = Cast<ACharacter>(inPawn);
    _k10Char = Cast<AK10CharacterBase>(inPawn);
	if( _k10Char != nullptr ) _movementAdapter = _k10Char->GetMovementAdapter();
	if( _character != nullptr ) _movement = _character->GetCharacterMovement();

	auto localPlayer = Cast<ULocalPlayer>(_character);
	RETURN_AND_LOG_IF_NULL( localPlayer, "localPlayer" )

	auto subsystem = localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
    subsystem->ClearAllMappings();
    if( _inputMapping != nullptr ) subsystem->AddMappingContext( _inputMapping, 0 );
	// Bind the actions

}

void AK10PlayerController::OnUnPossess()
{
	UE_LOG(LogTemp, Warning, TEXT("AK10PlayerController::OnUnPossess()"));
	Super::OnUnPossess();
    _pawn = nullptr;
    _character = nullptr;
    _k10Char = nullptr;
    _movementAdapter = nullptr;
}

// Called to bind functionality to input
void AK10PlayerController::SetupInputComponent()
{
	UE_LOG(LogTemp, Warning, TEXT("AK10PlayerController::SetupInputComponent()"));
	Super::SetupInputComponent();

    auto inputComponent = InputComponent;
	RETURN_AND_LOG_IF_NULL( inputComponent, "inputComponent" )

	inputComponent->BindAction("Jump", IE_Pressed, this, &AK10PlayerController::Jump);
	inputComponent->BindAction("Jump", IE_Released, this, &AK10PlayerController::StopJumping);
	
	inputComponent->BindAction("Crouch", IE_Pressed, this, &AK10PlayerController::Crouch);
	inputComponent->BindAction("Crouch", IE_Released, this, &AK10PlayerController::StopCrouch);
	
	// inputComponent->BindAxis("MoveForward", this, &AK10PlayerController::MoveForward);
	// inputComponent->BindAxis("MoveRight", this, &AK10PlayerController::MoveRight);
	
	// inputComponent->BindAxis("Turn", this, &AK10PlayerController::AddControllerYawInput);
	// inputComponent->BindAxis("TurnRate", this, &AK10PlayerController::TurnAtRate);
	// inputComponent->BindAxis("LookUp", this, &AK10PlayerController::AddControllerPitchInput);
	// inputComponent->BindAxis("LookUpRate", this, &AK10PlayerController::LookUpAtRate);
	
	auto enhancedInput = Cast<UEnhancedInputComponent>(inputComponent);
	RETURN_AND_LOG_IF_NULL( enhancedInput, "enhancedInput" )

	if( _moveAction ) enhancedInput->BindAction( _moveAction, ETriggerEvent::Triggered, this, &AK10PlayerController::Move );
	if( _lookAction ) enhancedInput->BindAction( _lookAction, ETriggerEvent::Triggered, this, &AK10PlayerController::Look );
}
 
void AK10PlayerController::Move( const FInputActionValue& value )
{
	if( _movementAdapter == nullptr ) return;
    const FVector2D moveValue = value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("AK10PlayerController::Move( %s )"), *moveValue.ToString() );
	_movementAdapter->MoveForward( moveValue.Y );
	_movementAdapter->MoveRight( moveValue.X );
}
 
void AK10PlayerController::Look( const FInputActionValue& value )
{
	if( _pawn == nullptr ) return;
    const FVector2D lookValue = value.Get<FVector2D>();
	UE_LOG(LogTemp, Warning, TEXT("AK10PlayerController::Look( %s )"), *lookValue.ToString() );
	_pawn->AddControllerYawInput( lookValue.X );
	_pawn->AddControllerPitchInput( lookValue.Y );
}

void AK10PlayerController::Jump()
{
	if( _character == nullptr ) return;
	_character->Jump();
}

void AK10PlayerController::StopJumping()
{
	if( _character == nullptr ) return;
	_character->StopJumping();
}

void AK10PlayerController::Crouch()
{
	if( _movement == nullptr ) return;
	UE_LOG(LogTemp, Warning, TEXT("AK10PlayerController::Crouch() %s %s"), _movement->NavAgentProps.bCanCrouch  ?  TEXT( "bCanCrouch" ) : TEXT( "bCanNOTCrouch" ), _movement->CanEverCrouch() ?  TEXT( "CanEverCrouch" ) : TEXT( "CanNOTEverCrouch" ) );
	
	_movement->bWantsToCrouch = true;
}

void AK10PlayerController::StopCrouch()
{
	if( _movement == nullptr ) return;
	_movement->bWantsToCrouch = false;
}

void AK10PlayerController::AddControllerYawInput( float value )
{
	if( _pawn == nullptr ) return;
	// if( FMath::Abs( rate ) > SMALL_NUMBER ) UE_LOG(LogTemp, Warning, TEXT("AK10PlayerController::AddControllerYawInput( %f ) @ %fs"), value, GetTimeSinceStart() );
	_pawn->AddControllerYawInput( value );
}

void AK10PlayerController::AddControllerPitchInput( float value )
{
	if( _pawn == nullptr ) return;
	// if( FMath::Abs( rate ) > SMALL_NUMBER ) UE_LOG(LogTemp, Warning, TEXT("AK10PlayerController::AddControllerPitchInput( %f ) @ %fs"), value, GetTimeSinceStart() );
	_pawn->AddControllerPitchInput( value );
}

void AK10PlayerController::TurnAtRate(float rate)
{
	if( _pawn == nullptr ) return;
	// if( FMath::Abs( rate ) > SMALL_NUMBER ) UE_LOG(LogTemp, Warning, TEXT("AK10PlayerController::TurnAtRate( %f ) @ %fs"), rate, GetTimeSinceStart() );
	_pawn->AddControllerYawInput( rate * _baseTurnRate * GetWorld()->GetDeltaSeconds() );
}

void AK10PlayerController::LookUpAtRate(float rate)
{
	if( _pawn == nullptr ) return;
	// if( FMath::Abs( rate ) > SMALL_NUMBER ) UE_LOG(LogTemp, Warning, TEXT("AK10PlayerController::LookUpAtRate( %f ) @ %fs"), rate, GetTimeSinceStart() );
	_pawn->AddControllerPitchInput( rate * _baseLookUpRate * GetWorld()->GetDeltaSeconds() );
}

void AK10PlayerController::MoveForward(float value)
{
	// if( FMath::Abs( value ) > SMALL_NUMBER ) UE_LOG(LogTemp, Warning, TEXT("AK10PlayerController::MoveForward( %f ) _movementAdapter = %s"), value, ( _movementAdapter != nullptr ) ?  TEXT( "Valid" ) : TEXT( "NULL" ) );
	if( _movementAdapter != nullptr ) _movementAdapter->MoveForward( value );
}

void AK10PlayerController::MoveRight(float value)
{
	// if( FMath::Abs( value ) > SMALL_NUMBER ) UE_LOG(LogTemp, Warning, TEXT("AK10PlayerController::MoveRight( %f ) _movementAdapter = %s"), value, ( _movementAdapter != nullptr ) ?  TEXT( "Valid" ) : TEXT( "NULL" ) );
	if( _movementAdapter != nullptr )  _movementAdapter->MoveRight( value );
}