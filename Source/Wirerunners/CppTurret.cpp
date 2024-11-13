// Fill out your copyright notice in the Description page of Project Settings.


#include "CppTurret.h"
#include "Kismet/kismetMathLibrary.h"
#include "TurretAnimInterface.h"

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
	
    GetWorldTimerManager().SetTimer(TimerHandle,this,&ACppTurret::ChangeBeamTarget,ChangeTargetDelay,true,1.0f);
}

// Called every frame
void ACppTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    UpdateLookAtTarget( DeltaTime);
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
    Beam->SetRelativeScale3D(FVector(Length/400, Beam->GetRelativeScale3D().Y, Beam->GetRelativeScale3D().Z));
    Beam->SetRelativeLocation(FVector(Length/(-80),0,0));
}
