// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/K10CharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"


// Sets default values
AK10CharacterBase::AK10CharacterBase()
{
	UE_LOG(LogTemp, Warning, TEXT("AK10CharacterBase::ctor()"));
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	
	auto rootName = RootComponent->GetAttachSocketName();
	UE_LOG(LogTemp, Warning, TEXT("AK10CharacterBase::ctor() RootComponent = %s / %s"), *rootName.ToString(), *RootComponent->GetClass()->GetName() );

	// UE_LOG(LogTemp, Warning, TEXT("AK10CharacterBase::ctor() _movementAdapter = %s"), ( _movementAdapter != nullptr ) ?  TEXT( "Valid" ) : TEXT( "NULL" ) );
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