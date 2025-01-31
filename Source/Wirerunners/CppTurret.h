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
    
    UPROPERTY(EditDefaultsOnly, Category = Shooting)
        UParticleSystemComponent* P_MuzzleFlash;
    
    UPROPERTY(EditDefaultsOnly, Category = Shooting)
        USoundBase* ShootSound;
    
    UPROPERTY()
        FTimerHandle ChangeTargetTimerHandle;
    
    UPROPERTY()
        FTimerHandle TraceTimerHandle;
    
    UPROPERTY()
        FTimerHandle ShootTimerHandle;
    
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
    
    UPROPERTY(EditAnywhere)
        float ShootRate = 1.0f;
    
    UPROPERTY(EditAnywhere)
        float ShootDelay = 1.0f; // delay it takes to shoot the 1st shot
    
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
    
    UFUNCTION()
        void Shoot();
    
public:	

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool CanShoot = true;

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
