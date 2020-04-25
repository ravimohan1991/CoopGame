// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/SRifle.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ASRifle::ASRifle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	RootComponent = SkeletalMeshComp;

}

// Called when the game starts or when spawned
void ASRifle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASRifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

