// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/ActorCameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/EngineTypes.h"

void UActorCameraComponent::Setup( USceneComponent * rootComponent )
{
	if( rootComponent == nullptr ) return;

	// Create a camera boom (pulls in towards the player if there is a collision)
	_cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	
	// _cameraBoom->SetupAttachment( rootComponent, FName( TEXT( "CameraAnchor" ) ) );
	_cameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character
	_cameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	_cameraBoom->SocketOffset = FVector( 0.0f, 40.0f, 0.0f ); // The camera follows at this distance behind the character
	_cameraBoom->SetRelativeLocation( FVector( 0.0f, 0.0f, 100.0f ) );

	// Create a follow camera
	_followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	// _followCamera->SetupAttachment(_cameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	_followCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	ParentComponentsToOwner();
	// SetShouldBeAttached(AttachParent != nullptr);
	
	auto rootName = rootComponent->GetAttachSocketName();
	
	UE_LOG(LogTemp, Warning, TEXT("UActorCameraComponent::Setup( RootComponent = %s(%s) )"), *(rootComponent->GetAttachSocketName()).ToString(), *rootComponent->GetClass()->GetName() );
	UE_LOG(LogTemp, Warning, TEXT("UActorCameraComponent::Setup( _cameraBoom = %s(%s) )"), *(_cameraBoom->GetAttachSocketName()).ToString(), *_cameraBoom->GetClass()->GetName() );
	// PrintHierarchy( TEXT( "UActorCameraComponent::Setup()" ) );
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

void UActorCameraComponent::ParentComponentsToOwner()
{
	auto owner = GetOwner();
	if( owner == nullptr ) return;
	auto rootComponent = owner->GetRootComponent();
	if( rootComponent == nullptr ) return;
	ParentComponents( rootComponent );
}

void UActorCameraComponent::ParentComponents( USceneComponent * rootComponent )
{
	if( rootComponent == nullptr ) return;
	if( _cameraBoom == nullptr ) return;
	_cameraBoom->AttachToComponent( rootComponent, FAttachmentTransformRules::KeepRelativeTransform, FName( TEXT( "CameraAnchor" ) ) );
	if( _followCamera == nullptr ) return;
	_followCamera->AttachToComponent( _cameraBoom, FAttachmentTransformRules::KeepRelativeTransform, USpringArmComponent::SocketName );
}


// Called when the game starts
void UActorCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	ParentComponentsToOwner();
	PrintHierarchy();
}

void UActorCameraComponent::PrintHierarchy()
{
	USceneComponent* comp = _followCamera;
	int i = 0;
	while( comp != nullptr && i < 10 )
	{
		UE_LOG(LogTemp, Warning, TEXT("hierarchy[%i] = %s(%s) "), i, *(comp->GetAttachSocketName()).ToString(), *comp->GetClass()->GetName() );
		comp = comp->GetAttachParent();
		i++;
	}
}


// Called every frame
void UActorCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// _followCamera->SetWorldLocation( _cameraBoom->GetUnfixedCameraPosition() );
	// ...
}

