// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/K10PlayerCameraManager.h"
#include "Components/CapsuleComponent.h"
#include "DrawDebugHelpers.h"

AK10PlayerCameraManager::AK10PlayerCameraManager()
{
	UE_LOG(LogTemp, Warning, TEXT("AK10PlayerCameraManager::ctor()") );
	// DefaultFOV = 90.f;
	_cameraCloserFOV = 120.f;
	_cameraDefaultDistance = 450.f;
	_cameraCloserDistance = 150.f;
	_currentDistance = _cameraDefaultDistance;
	_defaultTargetOffset = FVector( 0, 0, 148 );
	_rotatedTargetOffset = FVector( 0, 40, 40 );
	_checkCameraBlock = true;
	_hitSafeOffset = 15.f;
    _logValuesToConsole = false;
    _drawGizmos = false;
}

void AK10PlayerCameraManager::UpdateViewTarget(FTViewTarget& outVT, float deltaTime)
// void AK10PlayerCameraManager::UpdateCamera(float deltaTime)
{
	Super::UpdateViewTarget(outVT, deltaTime);
	
	// Get the player controller and pawn
	auto playerController = GetOwningPlayerController();
	if( playerController == nullptr ) return;

	auto pawn = playerController->GetPawn();
	if( pawn == nullptr ) return;
	
	auto pawnLocation = pawn->GetActorLocation();
	// Calculate the camera position and rotation
	auto pawnRotation = pawn->GetActorRotation();
	auto rotation = pawnRotation;
	
	auto controller = pawn->GetInstigatorController();
	if( controller != nullptr ) rotation = controller->GetControlRotation();

    auto fov = DefaultFOV;
	_currentDistance = _cameraDefaultDistance;
    auto pitch = rotation.Pitch;
    if( pitch < 180 ) // Elipse radius formula for distance when camera looking up
    {
        _currentDistance = CalculateCameraDistance( _cameraCloserDistance, _cameraDefaultDistance, FMath::DegreesToRadians( pitch ) );

        auto diff = ( _cameraCloserDistance - _cameraDefaultDistance );
        auto lerpValue = FMath::Clamp( FMath::Abs( pitch - 90 ) / 45, 0, 1 );
        // auto lerpPowered = FMath::Sqrt( lerpValue );
        fov = FMath::Lerp( _cameraCloserFOV, DefaultFOV, lerpValue );

        // DISPLAY_REPLACABLE_LOG_P4( 897964, "lerpValue:%f lerpPowered:%f diff:%f fov:%f", lerpValue, lerpPowered, diff, fov );
    } 

    auto halfHeight = pawn->GetDefaultHalfHeight(); 

    auto character = Cast<ACharacter>(pawn);
    if( character != nullptr )
    {
        auto capsule = character->GetCapsuleComponent();
        if( capsule != nullptr ) 
        {
            halfHeight = capsule->GetScaledCapsuleHalfHeight();
           DISPLAY_REPLACABLE_LOG_P1( 651654, "currentHalfHeight:%f", halfHeight );
        }
    }

    auto pawnOffsetedOrigin = pawnLocation + pawnRotation.RotateVector( ( FVector( 0, 0, -halfHeight ) ) + _defaultTargetOffset );
	auto focusPoint = pawnOffsetedOrigin + rotation.RotateVector( _rotatedTargetOffset );
	FVector location = focusPoint - ( rotation.Vector() * _currentDistance );

    DrawDebugSphere( GetWorld(), pawnOffsetedOrigin, 5, 12, FColor::Red, false, -1, -100 );
    DrawDebugSphere( GetWorld(), focusPoint, 5, 12, FColor::Red );

    // DISPLAY_REPLACABLE_LOG_P4( 98798, "rotation:%s rotation.Vector:%s rotation.Pitch:%f _currentDistance:%f", *rotation.ToString(), *rotation.Vector().ToString(), pitch, _currentDistance );

    if( _logValuesToConsole ) DISPLAY_REPLACABLE_LOG_P4( 16542, "location:%s pawnLocation:%s focusPoint:%s distance:%f", *pawnLocation.ToString(), *location.ToString(), *focusPoint.ToString(), _currentDistance );

    if( _drawGizmos )
    {
        DrawDebugPoint(GetWorld(), pawnOffsetedOrigin, 25.f, FColor::Red, false, -1, 0);
        DrawDebugLine(GetWorld(), pawnOffsetedOrigin, focusPoint, FColor::Yellow, false, -1, 0, 5.0f);
        DrawDebugPoint(GetWorld(), focusPoint, 25.f, FColor::Red, false, -1, 0);
        DrawDebugLine(GetWorld(), pawnLocation, pawnOffsetedOrigin, FColor::Yellow, false, -1, 0, 5.0f);
        DrawDebugPoint(GetWorld(), pawnLocation, 25.f, FColor::Red, false, -1, 0);
    }

	if( _checkCameraBlock )
	{
		FHitResult hitResult;
		FCollisionQueryParams collisionParams;

        auto dir = ( location - focusPoint ).GetSafeNormal();
		if (GetWorld()->LineTraceSingleByChannel(hitResult, focusPoint, location + dir * _hitSafeOffset, ECC_Visibility, collisionParams))
		{
			auto newLocation = hitResult.Location - dir * _hitSafeOffset;
            if( _drawGizmos ) 
            {
                DrawDebugLine(GetWorld(), newLocation, focusPoint, FColor::Green, false, -1, 0, 5.0f);
                DrawDebugLine(GetWorld(), newLocation, location, FColor::Red, false, -1, 0, 5.0f);
                DrawDebugPoint(GetWorld(), newLocation, 25.f, FColor::Red, false, -1, 0);
            }
			// If the trace hit something, adjust the camera location
			location = newLocation;
		}
        else
        {
            if( _drawGizmos ) DrawDebugLine(GetWorld(), location, focusPoint, FColor::Green, false, -1, 0, 5.0f);
        }
	}
    else
    {
        if( _drawGizmos ) DrawDebugLine(GetWorld(), location, focusPoint, FColor::Green, false, -1, 0, 5.0f);
    }

	outVT.POV.FOV = fov;
	outVT.POV.Location = location;
    outVT.POV.Rotation = rotation;
}

float AK10PlayerCameraManager::CalculateCameraDistance( float minDist, float maxDist, float radAng )
{
    auto bCos = minDist * FMath::Cos( radAng );
    auto aSin = maxDist * FMath::Sin( radAng );
    return maxDist * minDist / ( FMath::Sqrt( bCos * bCos + aSin * aSin ) );
}