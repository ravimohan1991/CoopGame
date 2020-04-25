// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRifle.generated.h"

class USkeletalMeshComponent;

UCLASS()
class COOPGAME_API ASRifle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASRifle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Skeletal mesh component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* SkeletalMeshComp;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
