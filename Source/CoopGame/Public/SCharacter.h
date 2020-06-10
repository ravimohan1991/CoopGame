// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class ASRifle;

UCLASS()
class COOPGAME_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**
	* Move forward/backward logic
	*
	* @param Value The movement multiplier
	*/
	void MoveForward(float Value);

	/**
	* Move right/left logic
	*
	* @param Value The movement multiplier
	*/
	void MoveRight(float Value);

	/** Logic for crouching */
	void BeginCrouch();

	/** Logic for uncrouch */
	void EndCrouch();

protected:
	/** The character's camera component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	/** Character's spring arm component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SpringArmComp;

	/** Default field of view set during BeginPlay */
	float DefaultFOV;

	/** If the character wants to zoom */
	bool bWantsToZoom;

	/** The zooming FOV scale */
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	float ZoomedFOV;

	/** Start zooming */
	void BeginZoom();

	/** Stop zooming (zoom out) */
	void EndZoom();

	/** Speed of zooming */
	UPROPERTY(EditDefaultsOnly, Category = "Player",  meta = (clampmin = 0.1f, clampmax = 100.0f))
	float ZoomSpeed;

	/** The weapon our character is holding now. */
	ASRifle* CurrWeapon;

	/** Fire logic with keybind. */
	void Fire();

	/** The class of default weapon. */
	UPROPERTY(EditDefaultsOnly, Category = "Player")
	TSubclassOf<ASRifle> StarterWeaponClass;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Returns	Pawn's eye location which is camera location */
	virtual FVector GetPawnViewLocation() const;

};
