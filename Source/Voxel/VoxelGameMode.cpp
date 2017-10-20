// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "VoxelGameMode.h"
#include "VoxelHUD.h"
#include "VoxelCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVoxelGameMode::AVoxelGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerFinder(TEXT("/Game/VoxelPlayerController"));
	PlayerControllerClass = PlayerControllerFinder.Class;

	// use our custom HUD class
	HUDClass = AVoxelHUD::StaticClass();
}
