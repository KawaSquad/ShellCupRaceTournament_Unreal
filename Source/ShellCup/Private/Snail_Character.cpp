// Fill out your copyright notice in the Description page of Project Settings.


#include "Snail_Character.h"

// Sets default values
ASnail_Character::ASnail_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASnail_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASnail_Character::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value);
}
void ASnail_Character::TorqueRight(float Value)
{

	AddMovementInput(GetActorRightVector() * Value);
}

// Called every frame
void ASnail_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASnail_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASnail_Character::MoveForward);
	PlayerInputComponent->BindAxis("TorqueRight", this, &ASnail_Character::TorqueRight);

}

