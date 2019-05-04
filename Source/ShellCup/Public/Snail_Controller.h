// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DefaultPawn.h"
#include "Snail_Controller.generated.h"

class USphereComponent;
class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;
class UAnimInstance;
class UPawnMovementComponent;

UCLASS()
class SHELLCUP_API ASnail_Controller : public ADefaultPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASnail_Controller();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	//	USphereComponent * SphereCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		UArrowComponent * DirectionComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Component")
		USkeletalMeshComponent * SnailMeshComp;
	UAnimInstance * AnimSnail;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		USkeletalMeshComponent * ImpMeshComp;
	UAnimInstance * AnimImp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		USpringArmComponent * SpringArmCam;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		UCameraComponent * ThirdCam;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
		UPawnMovementComponent * MoveComp;

	UPROPERTY(EditAnywhere, Category = "Snail_Controller")
		float SpeedForward = 100;
	UPROPERTY(EditAnywhere, Category = "Snail_Controller")
		float SpeedTorque = 100;

	void MoveForward(float Value);
	void TurnRight(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void StickOnFloor();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
