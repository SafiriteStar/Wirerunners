// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "CppTurret.generated.h"

UCLASS()
class WIRERUNNERS_API ACppTurret : public AActor
{
	GENERATED_BODY()
    
private:
    UPROPERTY(VisibleAnywhere)
        USceneComponent* Root;
    
    UPROPERTY(EditDefaultsOnly)
        USkeletalMeshComponent* TurretMesh;
    
    UPROPERTY(VisibleAnywhere)
        UStaticMeshComponent* Beam;
    
    UPROPERTY(VisibleAnywhere)
        USceneComponent* Target1;
    
    UPROPERTY(VisibleAnywhere)
        USceneComponent* Target2;
    
    UPROPERTY(VisibleAnywhere)
        USceneComponent* BeamTarget;
    
    UPROPERTY()
        FTimerHandle ChangeTargetTimerHandle;
    
    UPROPERTY()
        FTimerHandle TraceTimerHandle;
    
    // Rotation related variables
    int TimerCount = 0;
    FRotator LookAtRotation;
    FRotator TargetRotation;
    FRotator RotationDelta;
    
    const float cubeSize = 100.0f;
    
    UPROPERTY(EditAnywhere)
        float ChangeTargetDelay = 5.0f;
    
    UPROPERTY(EditAnywhere)
        float RotationRateMultiplier = 1.0f;
    
    UPROPERTY(EditAnywhere)
        float RotationToPlayerVelocity = 100.0f;
    
    UPROPERTY()
        AActor* Enemy = nullptr;
    
    UFUNCTION()
        void UpdateLookAtTarget(float DeltaTime);
    
    UFUNCTION()
        void ChangeBeamTarget();
    
    UFUNCTION(BlueprintCallable)
        void SetBeamLength(float Length);
    
    UFUNCTION()
        void TraceBeam();
    
    UFUNCTION()
        void CheckEnemy(AActor* HitActor); // change to CheckPlayer (and every other Enemy) when on Visual Studio
    
    UFUNCTION()
        void FollowEnemy(float DeltaTime); // change to FollowPlayer
    
public:	
	// Sets default values for this actor's properties
	ACppTurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    // beam length
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float BeamLength = 1000.0f;
        

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
