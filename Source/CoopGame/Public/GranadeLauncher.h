// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GranadeLauncher.generated.h"

class USkeletalMeshComponent;

UCLASS()
class COOPGAME_API AGranadeLauncher : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGranadeLauncher();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Skeletal mesh component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* SkeletalMeshComp;

	/** Fire logic */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void Fire();

	/** Type of damage */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

	/** Type of projectile */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AActor> ProjectileActor;

	/** Muzzle socket name */
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	FName MuzzleSocketName;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
