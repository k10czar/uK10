// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/K10PlayerCameraManager.h"

AK10PlayerCameraManager::AK10PlayerCameraManager()
{
	UE_LOG(LogTemp, Warning, TEXT("AK10PlayerCameraManager::ctor()") );
	// DefaultFOV = 90.f;
	ZoomedFOV = 60.f;
	_cameraDefaultDistance = 450.f;
	_cameraCloserDistance = 150.f;
	_currentDistance = _cameraDefaultDistance;
	_defaultTargetOffset = FVector( 0, 0, 60 );
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
	_currentDistance = _cameraDefaultDistance;
	auto pawnRotation = pawn->GetActorRotation();
	auto rotation = pawnRotation;
	
	auto controller = pawn->GetInstigatorController();
	if( controller != nullptr ) rotation = controller->GetControlRotation();

    auto pitch = rotation.Pitch;
    auto a = _cameraDefaultDistance;
    auto b = _cameraCloserDistance;
    if( pitch < 180 )
    {
        auto radAng = FMath::DegreesToRadians( pitch ); // * PI / 180;
        auto bCos = b * FMath::Cos( radAng );
        auto aSin = a * FMath::Sin( radAng );
        _currentDistance = a * b / ( FMath::Sqrt( bCos * bCos + aSin * aSin ) );
    } 

    auto pawnOffsetedOrigin = pawnLocation + _defaultTargetOffset;
	auto focusPoint = pawnOffsetedOrigin + rotation.RotateVector( _rotatedTargetOffset );
	FVector location = focusPoint - ( rotation.Vector() * _currentDistance );

    // GEngine->AddOnScreenDebugMessage( 1, 5.f, FColor::Yellow, FString::Printf( TEXT("rotation:%s rotation.Vector:%s rotation.Pitch:%f _currentDistance:%f"), *rotation.ToString(), *rotation.Vector().ToString(), pitch, _currentDistance ) );

    if( _logValuesToConsole ) GEngine->AddOnScreenDebugMessage( 1, 5.f, FColor::Yellow, FString::Printf( TEXT("location:%s pawnLocation:%s focusPoint:%s distance:%f"), *pawnLocation.ToString(), *location.ToString(), *focusPoint.ToString(), _currentDistance ) );

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

	outVT.POV.Location = location;
    outVT.POV.Rotation = rotation;
}