// Fill out your copyright notice in the Description page of Project Settings.


#include "WirerunningShip.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"

// Sets default values
AWirerunningShip::AWirerunningShip()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWirerunningShip::BeginPlay()
{
	// Call the base class
	Super::BeginPlay();
}


// Called to bind functionality to input
void AWirerunningShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	// Set up the action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWirerunningShip::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWirerunningShip::Look);

		// Shooting
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AWirerunningShip::Shoot);

		// Exit
		EnhancedInputComponent->BindAction(ExitAction, ETriggerEvent::Triggered, this, &AWirerunningShip::Exit);

	}
}

void AWirerunningShip::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr) {
		// Basic horizontal plane movement
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AWirerunningShip::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();



	//FQuat RotationStep = FQuat(FVector(0.0f, 0.0f, 1.0f)), FMath::DegreesToRadians(45.0f));

	if (Controller != nullptr) {
		AddActorWorldRotation(RotationStepPerInput, false, nullptr, ETeleportType::None);
		/*
			FVector newForward = Target - Source;
			newForward.Normalize();

			const FVector WorldUp(0.0f, 0.0f, 1.0f);

			FVector newRight = FVector::Cross(toTarget, WorldUp);
			FVector newUp = FVector::Cross(newRight, newForward);

			return FTransform(newForward, newRight, newUp, Source);
		*/

		//AddMovementInput(GetActorForwardVector(), LookVector.Y);
		//AddMovementInput(GetActorRightVector(), LookVector.X);
	}

	// Vector.Rotation().Quaternian
}

void AWirerunningShip::Shoot(const FInputActionValue& Value)
{

}

void AWirerunningShip::Exit(const FInputActionValue& Value)
{

}

// Called every frame
void AWirerunningShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



