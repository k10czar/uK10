// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/K10CharacterMovementComponent.h"

// Sets default values for this component's properties
UK10CharacterMovementComponent::UK10CharacterMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UK10CharacterMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	_startTime = FPlatformTime::Seconds();
	// ...
	
}

float UK10CharacterMovementComponent::GetTimeSinceStart() { return FPlatformTime::Seconds() - _startTime; }


// Called every frame
void UK10CharacterMovementComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UK10CharacterMovementComponent::MoveForward( float value )
{
	// auto owner = GetOwner();
	
	// if( owner == nullptr )
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Fail to GetOwner() UK10CharacterMovementComponent::MoveForward( %f ) @ %fs"), value, GetTimeSinceStart() );
	// 	return;
	// }

	// auto controller = owner->GetInstigatorController();
	
	// if( controller == nullptr )
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Fail to GetInstigatorController() UK10CharacterMovementComponent::MoveForward( %f ) @ %fs"), value, GetTimeSinceStart() );
	// 	return;
	// }

	// auto pawn = Cast<APawn>( owner );
	
	// if( pawn == nullptr ) 
	// {
	// 	UE_LOG(LogTemp, Error, TEXT("Fail to Cast actor to Pawn() UK10CharacterMovementComponent::MoveForward( %f ) @ %fs"), value, GetTimeSinceStart() );
	// 	return;
	// }
	
	// if ((controller != NULL) && (value != 0.0f))
	// {
	// 	// UE_LOG(LogTemp, Display, TEXT("AK10CharacterBase::MoveForward( %f ) @ %fs"), value, GetTimeSinceStart() );
	// 	// find out which way is forward
	// 	const FRotator Rotation = controller->GetControlRotation();
	// 	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// 	// get forward vector
	// 	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// 	pawn->AddMovementInput(Direction, value);
	// }
}

void UK10CharacterMovementComponent::MoveRight( float value )
{
// 	auto owner = GetOwner();

// 	if( owner == nullptr )
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("Fail to GetOwner() UK10CharacterMovementComponent::MoveRight( %f ) @ %fs"), value, GetTimeSinceStart() );
// 		return;
// 	}

// 	auto controller = owner->GetInstigatorController();
	
// 	if( controller == nullptr ) 
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("Fail to GetInstigatorController() UK10CharacterMovementComponent::MoveRight( %f ) @ %fs"), value, GetTimeSinceStart() );
// 		return;
// 	}

// 	auto pawn = Cast<APawn>( owner );
	
// 	if( pawn == nullptr ) 
// 	{
// 		UE_LOG(LogTemp, Error, TEXT("Fail to Cast actor to Pawn() UK10CharacterMovementComponent::MoveRight( %f ) @ %fs"), value, GetTimeSinceStart() );
// 		return;
// 	}

// 	if ( (controller != NULL) && (value != 0.0f) )
// 	{
// 		// UE_LOG(LogTemp, Display, TEXT("AK10CharacterBase::MoveRight( %f ) @ %fs"), value, GetTimeSinceStart() );
// 		// find out which way is right
// 		const FRotator Rotation = controller->GetControlRotation();
// 		const FRotator YawRotation(0, Rotation.Yaw, 0);
	
// 		// get right vector 
// 		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
// 		// add movement in that direction
// 		pawn->AddMovementInput(Direction, value);
// 	}
}

