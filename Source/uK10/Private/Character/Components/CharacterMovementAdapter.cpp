// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/CharacterMovementAdapter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Log/K10Macros.h"
// #include "GameFramework/Character.h"

// Sets default values for this component's properties
UCharacterMovementAdapter::UCharacterMovementAdapter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	TrySetCharacterMovementData();
}

void UCharacterMovementAdapter::TrySetCharacterMovementData()
{
	auto owner = GetOwner();
	RETURN_AND_LOG_IF_NULL( owner, "owner" )
	
	auto pawn = Cast<APawn>(owner);
	RETURN_AND_LOG_IF_NULL( pawn, "pawn" )
	pawn->bUseControllerRotationPitch = false;
	pawn->bUseControllerRotationYaw = false;
	pawn->bUseControllerRotationRoll = false;

	RETURN_AND_LOG_IF_NULL( owner, "owner" )
    auto character = Cast<ACharacter>(owner);
	RETURN_AND_LOG_IF_NULL( character, "character" )
	auto charMovement = character->GetCharacterMovement();
	RETURN_AND_LOG_IF_NULL( charMovement, "charMovement" )
	
	charMovement->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	charMovement->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	charMovement->JumpZVelocity = 600.f;
	charMovement->AirControl = 0.5f;
	charMovement->NavAgentProps.bCanCrouch = true;
}


// Called when the game starts
void UCharacterMovementAdapter::BeginPlay()
{
	Super::BeginPlay();

	_startTime = FPlatformTime::Seconds();
	// ...
	
}

float UCharacterMovementAdapter::GetTimeSinceStart() { return FPlatformTime::Seconds() - _startTime; }


// Called every frame
void UCharacterMovementAdapter::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UCharacterMovementAdapter::MoveForward( float value )
{
	auto owner = GetOwner();
	
	if( owner == nullptr )
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to GetOwner() UCharacterMovementAdapter::MoveForward( %f ) @ %fs"), value, GetTimeSinceStart() );
		return;
	}

	auto controller = owner->GetInstigatorController();
	
	if( controller == nullptr )
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to GetInstigatorController() UCharacterMovementAdapter::MoveForward( %f ) @ %fs"), value, GetTimeSinceStart() );
		return;
	}

	auto pawn = Cast<APawn>( owner );
	
	if( pawn == nullptr ) 
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to Cast actor to Pawn() UCharacterMovementAdapter::MoveForward( %f ) @ %fs"), value, GetTimeSinceStart() );
		return;
	}
	
	if ((controller != NULL) && (value != 0.0f))
	{
		// UE_LOG(LogTemp, Display, TEXT("AK10CharacterBase::MoveForward( %f ) @ %fs"), value, GetTimeSinceStart() );
		// find out which way is forward
		const FRotator Rotation = controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		pawn->AddMovementInput(Direction, value);
	}
}

void UCharacterMovementAdapter::MoveRight( float value )
{
	auto owner = GetOwner();

	if( owner == nullptr )
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to GetOwner() UCharacterMovementAdapter::MoveRight( %f ) @ %fs"), value, GetTimeSinceStart() );
		return;
	}

	auto controller = owner->GetInstigatorController();
	
	if( controller == nullptr ) 
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to GetInstigatorController() UCharacterMovementAdapter::MoveRight( %f ) @ %fs"), value, GetTimeSinceStart() );
		return;
	}

	auto pawn = Cast<APawn>( owner );
	
	if( pawn == nullptr ) 
	{
		UE_LOG(LogTemp, Error, TEXT("Fail to Cast actor to Pawn() UCharacterMovementAdapter::MoveRight( %f ) @ %fs"), value, GetTimeSinceStart() );
		return;
	}

	if ( (controller != NULL) && (value != 0.0f) )
	{
		// UE_LOG(LogTemp, Display, TEXT("AK10CharacterBase::MoveRight( %f ) @ %fs"), value, GetTimeSinceStart() );
		// find out which way is right
		const FRotator Rotation = controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		pawn->AddMovementInput(Direction, value);
	}
}
