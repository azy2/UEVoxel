// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "VoxelCharacter.h"
#include "VoxelProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "SettingsManager.h"
#include "WorldManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AVoxelCharacter

AVoxelCharacter::AVoxelCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(40.f, 75.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 75.0f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;
}

void AVoxelCharacter::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	chunkLoader.findChunksToLoad(this->GetActorLocation());
	chunkLoader.loadAndRenderChunks();
	chunkLoader.deleteChunks(this->GetActorLocation(), GetWorld());
}

void AVoxelCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	FVector v = GetActorLocation();
	v.Z = (USettingsManager::worldHeight / 2) * USettingsManager::voxelToUUFactor;
	this->SetActorLocation(v);

	TArray<AActor*> outActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWorldManager::StaticClass(), outActors);
	chunkLoader.setWorldManager((AWorldManager*)outActors[0]);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AVoxelCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &AVoxelCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVoxelCharacter::MoveRight);

	PlayerInputComponent->BindAction("Click", IE_Pressed, this, &AVoxelCharacter::Click);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AVoxelCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AVoxelCharacter::LookUpAtRate);
}

void AVoxelCharacter::Click() {

}

void AVoxelCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AVoxelCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AVoxelCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AVoxelCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}
