// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "K10PlayerCameraManager.generated.h"

/**
 * 
 */
UCLASS()
class UK10_API AK10PlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

public:
	AK10PlayerCameraManager();
	
	virtual void UpdateViewTarget(FTViewTarget& OutVT, float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FVector _defaultTargetOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	FVector _rotatedTargetOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float ZoomedFOV;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float _cameraDefaultDistance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	float _cameraCloserDistance;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blocking)
	bool _checkCameraBlock;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blocking)
	float _hitSafeOffset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	bool _logValuesToConsole;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Debug)
	bool _drawGizmos;
	
private:
	float _currentDistance;
};
