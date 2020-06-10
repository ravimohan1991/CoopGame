// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SRifle.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

static int32 DebugWeaponDrawing = 0;
FAutoConsoleVariableRef CVARDebugWeaponDrawing(TEXT("COOP.DebugWeapons"), DebugWeaponDrawing, TEXT("Draw debug lines for weapons"), ECVF_Cheat);

// Sets default values
ASRifle::ASRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	RootComponent = SkeletalMeshComp;

	MuzzleSocketName = "MuzzleSocket";

}

// Called when the game starts or when spawned
void ASRifle::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASRifle::Fire()
{
	AActor* MyOwner = GetOwner();

	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;

		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector EndTrace = EyeLocation + EyeRotation.Vector() * 10000;
		// Trace routine
		FHitResult HitR;
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this);
		CollisionParams.AddIgnoredActor(MyOwner);
		CollisionParams.bTraceComplex = true;
		CollisionParams.bReturnPhysicalMaterial = true;

		FVector TracerEndPoint = EndTrace;

		if (GetWorld()->LineTraceSingleByChannel(HitR, EyeLocation, EndTrace, ECC_Visibility, CollisionParams))
		{
			// Takedamage
			AActor* DActor = HitR.GetActor();
			TracerEndPoint = HitR.ImpactPoint;
			UGameplayStatics::ApplyPointDamage(DActor, 20.0f, EyeRotation.Vector(), HitR, MyOwner->GetInstigatorController(), this, DamageType);

			EPhysicalSurface SurfaceType =  UPhysicalMaterial::DetermineSurfaceType(HitR.PhysMaterial.Get());
			UParticleSystem* SelectedEffect = nullptr;

			switch (SurfaceType)
			{
			case SurfaceType1:
			case SurfaceType2:
				SelectedEffect = FleshTraceHitEffect;
				break;
			default:
				SelectedEffect = DefaultTraceHitEffect;
				break;
			}

			if (SelectedEffect)
			{
				UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), SelectedEffect, HitR.ImpactPoint, HitR.ImpactNormal.Rotation());
			}
		}

		if (DebugWeaponDrawing > 0)
		{
			DrawDebugLine(GetWorld(), EyeLocation, EndTrace, FColor::White, false, 2.0f, 0, 1.0f);
		}
		
		PlayFireEffects(TracerEndPoint);
	}
}


void ASRifle::PlayFireEffects(FVector EndPoint)
{
	if (MuzzleEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, SkeletalMeshComp, MuzzleSocketName);
	}

	if (TrailEffect)
	{
		FVector MuzzleLocation = SkeletalMeshComp->GetSocketLocation(MuzzleSocketName);

		UParticleSystemComponent* TrailComp = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TrailEffect, MuzzleLocation);

		if (TrailComp)
		{
			TrailComp->SetVectorParameter("BeamEnd", EndPoint);
		}
	}

	APawn* MyPawn = Cast<APawn>(GetOwner());

	if (MyPawn)
	{
		APlayerController* PC = Cast<APlayerController>(MyPawn->GetController());
		if (PC)
		{
			PC->ClientPlayCameraShake(FireCamShake);
		}
	}
}

// Called every frame
void ASRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

