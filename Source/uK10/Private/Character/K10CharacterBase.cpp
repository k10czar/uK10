// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/K10CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Character/Components/ActorCameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"


// Sets default values
AK10CharacterBase::AK10CharacterBase()
{
	UE_LOG(LogTemp, Warning, TEXT("AK10CharacterBase::ctor()"));
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	_baseTurnRate = 45.f;
	_baseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.5f;
	
	_movementAdapter = CreateDefaultSubobject<UCharacterMovementAdapter>( TEXT( "MovementAdapter" ) );
	_actorCameraComponent = CreateDefaultSubobject<UActorCameraComponent>( TEXT( "ActorCameraComponent" ) );

	// _actorCameraComponent->Setup( RootComponent );
	
	auto rootName = RootComponent->GetAttachSocketName();
	UE_LOG(LogTemp, Warning, TEXT("AK10CharacterBase::ctor() RootComponent = %s / %s"), *rootName.ToString(), *RootComponent->GetClass()->GetName() );

	// UE_LOG(LogTemp, Warning, TEXT("AK10CharacterBase::ctor() _movementAdapter = %s"), ( _movementAdapter != nullptr ) ?  TEXT( "Valid" ) : TEXT( "NULL" ) );
	// UE_LOG(LogTemp, Warning, TEXT("AK10CharacterBase::ctor() _actorCameraComponent = %s"), ( _actorCameraComponent != nullptr ) ?  TEXT( "Valid" ) : TEXT( "NULL" ) );
}

float AK10CharacterBase::GetTimeSinceStart() { return FPlatformTime::Seconds() - _startTime; }

// Called when the game starts or when spawned
void AK10CharacterBase::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("AK10CharacterBase::BeginPlay()"));
	Super::BeginPlay();
	_startTime = FPlatformTime::Seconds();
}

// Called every frame
void AK10CharacterBase::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}

// Called to bind functionality to input
void AK10CharacterBase::SetupPlayerInputComponent(UInputComponent* playerInputComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("AK10CharacterBase::SetupPlayerInputComponent()"));
	Super::SetupPlayerInputComponent(playerInputComponent);

	check(playerInputComponent);
	playerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	playerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
	playerInputComponent->BindAxis("MoveForward", this, &AK10CharacterBase::MoveForward);
	playerInputComponent->BindAxis("MoveRight", this, &AK10CharacterBase::MoveRight);
	
	playerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	playerInputComponent->BindAxis("TurnRate", this, &AK10CharacterBase::TurnAtRate);
	playerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	playerInputComponent->BindAxis("LookUpRate", this, &AK10CharacterBase::LookUpAtRate);
}

void AK10CharacterBase::TurnAtRate(float rate)
{
	// if( FMath::Abs( rate ) > SMALL_NUMBER ) UE_LOG(LogTemp, Display, TEXT("AK10CharacterBase::TurnAtRate( %f ) @ %fs"), rate, GetTimeSinceStart() );
	// calculate delta for this frame from the rate information
	AddControllerYawInput(rate * _baseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AK10CharacterBase::LookUpAtRate(float rate)
{
	// if( FMath::Abs( rate ) > SMALL_NUMBER ) UE_LOG(LogTemp, Display, TEXT("AK10CharacterBase::LookUpAtRate( %f ) @ %fs"), rate, GetTimeSinceStart() );
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(rate * _baseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AK10CharacterBase::MoveForward(float value)
{
	// if( FMath::Abs( value ) > SMALL_NUMBER ) 
	// 	UE_LOG(LogTemp, Warning, TEXT("AK10CharacterBase::MoveForward( %f ) _movementAdapter = %s"), value, ( _movementAdapter != nullptr ) ?  TEXT( "Valid" ) : TEXT( "NULL" ) );
	if( _movementAdapter == nullptr ) return;
	_movementAdapter->MoveForward( value );
}

void AK10CharacterBase::MoveRight(float value)
{
	// if( FMath::Abs( value ) > SMALL_NUMBER ) 
	// 	UE_LOG(LogTemp, Warning, TEXT("AK10CharacterBase::MoveRight( %f ) _movementAdapter = %s"), value, ( _movementAdapter != nullptr ) ?  TEXT( "Valid" ) : TEXT( "NULL" ) );
	if( _movementAdapter == nullptr ) return;
	_movementAdapter->MoveRight( value );
}

