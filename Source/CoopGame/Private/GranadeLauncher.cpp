// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/GranadeLauncher.h"
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AGranadeLauncher::AGranadeLauncher()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = SkeletalMeshComp;

	MuzzleSocketName = "MuzzleFlashSocket";

}

// Called when the game starts or when spawned
void AGranadeLauncher::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGranadeLauncher::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AGranadeLauncher::Fire()
{
	AActor* MyOwner = GetOwner();

	if (MyOwner && ProjectileActor)
	{
		FVector SLocation = SkeletalMeshComp->GetSocketLocation(MuzzleSocketName);

		FVector EyeLocation;
		FRotator EyeRotation;

		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);
		
		//Set Spawn Collision Handling Override
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		ActorSpawnParams.Instigator = Cast<APawn>(MyOwner);
		      
		GetWorld()->SpawnActor<AActor>(ProjectileActor, SLocation, EyeRotation, ActorSpawnParams);
	}
}
