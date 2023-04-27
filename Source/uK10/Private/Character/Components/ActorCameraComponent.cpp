// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/ActorCameraComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneComponent.h"

void UActorCameraComponent::Setup( USceneComponent * rootComponent )
{
	if( rootComponent == nullptr ) return;

	// Create a camera boom (pulls in towards the player if there is a collision)
	_cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	_cameraBoom->SetupAttachment( rootComponent );
	_cameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character
	_cameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	_cameraBoom->SocketOffset = FVector( 0.0f, 40.0f, 0.0f ); // The camera follows at this distance behind the character
	_cameraBoom->SetRelativeLocation( FVector( 0.0f, 0.0f, 100.0f ) );

	// Create a follow camera
	_followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	_followCamera->SetupAttachment(_cameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	_followCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

// Sets default values for this component's properties
UActorCameraComponent::UActorCameraComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	auto owner = GetOwner();
	UE_LOG(LogTemp, Warning, TEXT("UActorCameraComponent::ctor() owner = %s"), ( owner != nullptr ) ?  TEXT( "Valid" ) : TEXT( "NULL" ) );

	if( owner == nullptr ) return;

	Setup( owner->GetRootComponent() );
}


// Called when the game starts
void UActorCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UActorCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

