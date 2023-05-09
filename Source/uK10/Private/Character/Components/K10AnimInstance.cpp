// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Components/K10AnimInstance.h"
#include "Character/K10CharacterBase.h"
#include "Log/K10Macros.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void UK10AnimInstance::NativeInitializeAnimation()
{
	DISPLAY_AND_CONSOLE_LOG( "UK10AnimInstance::NativeInitializeAnimation()" )
    Super::NativeInitializeAnimation();
    _character = Cast<AK10CharacterBase>(TryGetPawnOwner());
}

void UK10AnimInstance::NativeUpdateAnimation(float deltaTime)
{
	DISPLAY_AND_CONSOLE_LOG( "UK10AnimInstance::NativeInitializeAnimation( %f )", deltaTime )
    Super::NativeUpdateAnimation(deltaTime);

    if (!_character) return;

    FVector Velocity = _character->GetVelocity();
    Velocity.Z = 0.f;
    Speed = Velocity.Size();

    bIsInAir = _character->GetCharacterMovement()->IsFalling();
    bIsAccelerating = _character->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false;
    bIsCrouched = _character->bIsCrouched;

    // Offset Yaw for Strafing
    FRotator AimRotation = _character->GetBaseAimRotation();
    FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(_character->GetVelocity());
    FRotator DeltaRot = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation);
    DeltaRotation = FMath::RInterpTo(DeltaRotation, DeltaRot, deltaTime, 6.f);
    YawOffset = DeltaRotation.Yaw;

    CharacterRotationLastFrame = CharacterRotation;
    CharacterRotation = _character->GetActorRotation();
    const FRotator Delta = UKismetMathLibrary::NormalizedDeltaRotator(CharacterRotation, CharacterRotationLastFrame);
    const float Target = Delta.Yaw / deltaTime;
    const float Interp = FMath::FInterpTo(Lean, Target, deltaTime, 6.f);
    Lean = FMath::Clamp(Interp, -90.f, 90.f);
}