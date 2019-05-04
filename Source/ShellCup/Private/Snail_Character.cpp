#include "Snail_Character.h"

ASnail_Character::ASnail_Character()
{
	PrimaryActorTick.bCanEverTick = true;
}

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
	AddControllerYawInput(Value);
}

void ASnail_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASnail_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASnail_Character::MoveForward);
	PlayerInputComponent->BindAxis("TorqueRight", this, &ASnail_Character::TorqueRight);
}

