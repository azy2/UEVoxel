#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "WorldManager.h"
#include "VoxelPlayerController.generated.h"

UCLASS()
class VOXEL_API AVoxelPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void SetupInputComponent() override;

	void OnClick();

	virtual void BeginPlay();

private:
	AWorldManager *worldManager;

};
