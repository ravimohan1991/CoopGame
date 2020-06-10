// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SRifle.generated.h"

class USkeletalMeshComponent;
class UDamageType;
class UParticleSystem;
class UCameraShake;

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

	/** Type of damage */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

	/** Muzzle effects */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UParticleSystem* MuzzleEffect;

	/** Default hit effects */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UParticleSystem* DefaultTraceHitEffect;

	/** Flesh hit effects */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UParticleSystem* FleshTraceHitEffect;

	/** Trail effects */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	UParticleSystem* TrailEffect;

	/** Socket name */
	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
	FName MuzzleSocketName;

	/** Play muzzle effect, bullet trailing effects and camerashake. */
	void PlayFireEffects(FVector EndPoint);

	/** Camera shake class. */
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UCameraShake> FireCamShake;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Fire logic */
	UFUNCTION(BlueprintCallable, Category = "Gameplay")
	void Fire();
};
