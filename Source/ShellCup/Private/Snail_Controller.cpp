// Fill out your copyright notice in the Description page of Project Settings.


#include "Snail_Controller.h"
#include "Animation/AnimInstance.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASnail_Controller::ASnail_Controller()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DirectionComp = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction Comp"));

	SnailMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Snail Mesh Comp"));
	ImpMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Imp Mesh Comp"));

	SpringArmCam = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	ThirdCam = CreateDefaultSubobject<UCameraComponent>(TEXT("Third Cam"));

	//CollisionComponent->SetSphereRadius(10);
	//CollisionComponent->SetSimulatePhysics(true);
	//CollisionComponent->SetEnableGravity(false);
	//CollisionComponent->SetCollisionProfileName("BlockAllDynamic");

	DirectionComp->SetupAttachment(RootComponent);
	SpringArmCam->SetupAttachment(RootComponent);
	ThirdCam->SetupAttachment(SpringArmCam);

	SnailMeshComp->SetupAttachment(RootComponent);
	ImpMeshComp->SetupAttachment(SnailMeshComp);

	AnimSnail = SnailMeshComp->GetAnimInstance();
	AnimImp = ImpMeshComp->GetAnimInstance();
}

// Called when the game starts or when spawned
void ASnail_Controller::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASnail_Controller::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector() * Value * SpeedForward);
	//SphereCollider->AddForce(GetActorForwardVector() * Value * SpeedForward);
}

void ASnail_Controller::TurnRight(float Value)
{
	AddControllerRollInput(Value * SpeedForward);
	/*
	FRotator newRot = SphereCollider->GetRelativeRotationCache() + FRotator(0, (Value*SpeedTorque), 0);

	SphereCollider->SetRelativeRotation
	SetActorRotation(newRot);
	*/
}

// Called every frame
void ASnail_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	StickOnFloor();
}

void ASnail_Controller::StickOnFloor()
{
	FCollisionQueryParams * CastFloorTraceParams = new FCollisionQueryParams(FName(TEXT("Cast floor")));
	//CastFloorTraceParams.bTraceComplex = true;
	//CastFloorTraceParams.bReturnPhysicalMaterial = false;

	FHitResult * HitInfo = new FHitResult(ForceInit);
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + (GetActorUpVector() * -100.0f);

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor(1, 1, 1, 1));
	if (GetWorld()->LineTraceSingleByChannel(*HitInfo, StartLocation, EndLocation, ECC_Visibility, CastFloorTraceParams))
	{
		DrawDebugSphere(GetWorld(), HitInfo->ImpactPoint, 0.1, 64, FColor(1, 1, 1, 1));
		
		SetActorLocation(HitInfo->Location + (GetActorUpVector()*10));

		//FVector normal = HitInfo->ImpactNormal;
		//SetActorRotation(normal.Rotation());
	}
}

// Called to bind functionality to input
void ASnail_Controller::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASnail_Controller::MoveForward);
	PlayerInputComponent->BindAxis("TurnRight", this, &ASnail_Controller::TurnRight);
}

