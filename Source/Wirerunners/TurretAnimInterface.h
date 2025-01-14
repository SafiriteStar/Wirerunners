// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TurretAnimInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTurretAnimInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WIRERUNNERS_API ITurretAnimInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = turretAnimation)
    void UpdateLookAtRotation(FRotator Rotation);
};
