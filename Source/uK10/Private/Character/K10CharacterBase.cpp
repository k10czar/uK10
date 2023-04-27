// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/K10CharacterBase.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Character/K10CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


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
	GetCharacterMovement()->AirControl = 0.2f;
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	_cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	_cameraBoom->SetupAttachment(RootComponent);
	_cameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	_cameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	_followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	_followCamera->SetupAttachment(_cameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	_followCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	_movementAdapter = CreateDefaultSubobject<UK10CharacterMovementComponent>( TEXT( "MovementComponent" ) );
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
	if( _movementAdapter == nullptr ) return;
	_movementAdapter->MoveForward( value );

	// // if( FMath::Abs( value ) > SMALL_NUMBER ) UE_LOG(LogTemp, Display, TEXT("AK10CharacterBase::MoveForward( %f ) @ %fs"), value, GetTimeSinceStart() );
	// if ((Controller != NULL) && (value != 0.0f))
	// {
	// 	// find out which way is forward
	// 	const FRotator Rotation = Controller->GetControlRotation();
	// 	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// 	// get forward vector
	// 	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	// 	AddMovementInput(Direction, value);
	// }
}

void AK10CharacterBase::MoveRight(float value)
{
	if( _movementAdapter == nullptr ) return;
	_movementAdapter->MoveRight( value );

	// // if( FMath::Abs( value ) > SMALL_NUMBER ) UE_LOG(LogTemp, Display, TEXT("AK10CharacterBase::MoveRight( %f ) @ %fs"), value, GetTimeSinceStart() );
	// if ( (Controller != NULL) && (value != 0.0f) )
	// {
	// 	// find out which way is right
	// 	const FRotator Rotation = Controller->GetControlRotation();
	// 	const FRotator YawRotation(0, Rotation.Yaw, 0);
	
	// 	// get right vector 
	// 	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	// 	// add movement in that direction
	// 	AddMovementInput(Direction, value);
	// }
}

