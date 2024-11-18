// Fill out your copyright notice in the Description page of Project Settings.


#include "CppTurret.h"
#include "Kismet/kismetMathLibrary.h"

#include "CharacterInterface.h"

#include "TurretAnimInterface.h"

#define OUT

// Sets default values
ACppTurret::ACppTurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);
    
    TurretMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Turretmesh"));
    TurretMesh->SetupAttachment(Root);
    
    Beam = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Beam"));
    Beam->SetupAttachment(TurretMesh,TEXT("BeamSocket"));
    
    Target1 = CreateDefaultSubobject<USceneComponent>(TEXT("Target1"));
    Target1->SetupAttachment(Root);
    
    Target2 = CreateDefaultSubobject<USceneComponent>(TEXT("Target2"));
    Target2->SetupAttachment(Root);
    
    BeamTarget = CreateDefaultSubobject<USceneComponent>(TEXT("BeamTarget"));
    BeamTarget->SetupAttachment(Root);
    
    SetBeamLength(BeamLength);
}

// Called when the game starts or when spawned
void ACppTurret::BeginPlay()
{
	Super::BeginPlay();
	
    GetWorldTimerManager().SetTimer(ChangeTargetTimerHandle,this,&ACppTurret::ChangeBeamTarget,ChangeTargetDelay,true,1.0f);
    
    GetWorldTimerManager().SetTimer(TraceTimerHandle,this,&ACppTurret::TraceBeam,0.1f,true,0.1f);
}

// Called every frame
void ACppTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
    if (Enemy)
    {
        FollowEnemy(DeltaTime);
    }
    else
    {
        UpdateLookAtTarget(DeltaTime);
    }

    //UpdateLookAtTarget(DeltaTime);
    
    TraceBeam();
}

void ACppTurret::UpdateLookAtTarget(float DeltaTime)
{
    if (LookAtRotation.Equals(TargetRotation,1.0f))
    {
        return;
    }
    
    LookAtRotation += RotationDelta * RotationRateMultiplier * DeltaTime;
    
    if (TurretMesh->GetAnimInstance()->Implements<UTurretAnimInterface>())
    {
        ITurretAnimInterface::Execute_UpdateLookAtRotation(TurretMesh->GetAnimInstance(), LookAtRotation);
    }
}

void ACppTurret::ChangeBeamTarget()
{
    TimerCount++;
    
    if (TimerCount%2 == 0)
    {
        BeamTarget->SetWorldLocation(Target1->GetComponentLocation());
    }
    else
    {
        BeamTarget->SetWorldLocation(Target2->GetComponentLocation());
    }
    
    FVector Start = TurretMesh->GetSocketLocation("BeamSocket");
    FVector End = BeamTarget->GetComponentLocation();
    TargetRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);
    
    RotationDelta = TargetRotation - LookAtRotation;
    RotationDelta.Normalize();
}

void ACppTurret::SetBeamLength(float Length)
{
    //Beam->SetRelativeScale3D(FVector(Length/cubeSize, Beam->GetRelativeScale3D().Y, Beam->GetRelativeScale3D().Z));
    //Beam->SetRelativeLocation(FVector(Length/2.0f,0,0));
    
    Beam->SetRelativeScale3D(FVector(Length/400, Beam->GetRelativeScale3D().Y, Beam->GetRelativeScale3D().Z));
    Beam->SetRelativeLocation(FVector(Length/(-80),0,0));
}

void ACppTurret::TraceBeam()
{
    FHitResult HitResult;
    
    FVector Start = TurretMesh->GetSocketLocation("BeamSocket");
    FVector End = Start + Beam->GetForwardVector() * BeamLength;
    
    FCollisionQueryParams CollQueryParams;
    CollQueryParams.AddIgnoredActor(this);
    
    bool bHit = GetWorld()->LineTraceSingleByChannel(
                                                     OUT HitResult,
                                                     Start,
                                                     End,
                                                     ECollisionChannel::ECC_Camera,
                                                     CollQueryParams
                                                     );
    
    if (bHit)
    {
        SetBeamLength(HitResult.Distance);
        CheckEnemy(HitResult.GetActor());
    }
    else
    {
        SetBeamLength(BeamLength);
    }
}

void ACppTurret::CheckEnemy(AActor* HitActor)
{
    if (HitActor->Implements<UCharacterInterface>())
    {
        bool bEnemy = ICharacterInterface::Execute_IsEnemy(HitActor);
        if (bEnemy)
        {
            Enemy = HitActor;
            UE_LOG(LogTemp, Warning, TEXT("Player Detected"));
        }
        else
        {
            if (Enemy != nullptr)
            {
                Enemy = nullptr;
                UE_LOG(LogTemp, Warning, TEXT("Player Lost"));
            }
        }
    }
    else
    {
        Enemy = nullptr;
        UE_LOG(LogTemp, Warning, TEXT("Not a player"));
    }
}

void ACppTurret::FollowEnemy(float DeltaTime)
{
    FVector Start = TurretMesh->GetSocketLocation("BeamSocket");
    FVector End = Enemy->GetActorLocation();
    
    FRotator RotationToEnemy = UKismetMathLibrary::FindLookAtRotation(Start, End);
    
    LookAtRotation = FMath::RInterpTo(LookAtRotation, RotationToEnemy, DeltaTime, RotationToPlayerVelocity);
    
    if (TurretMesh->GetAnimInstance()->Implements<UTurretAnimInterface>())
    {
        ITurretAnimInterface::Execute_UpdateLookAtRotation(TurretMesh->GetAnimInstance(), LookAtRotation);
    }
}
