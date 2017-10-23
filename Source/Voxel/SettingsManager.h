#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SettingsManager.generated.h"

UCLASS()
class VOXEL_API USettingsManager : public UObject
{
	GENERATED_BODY()
	
public:
	static const int viewDistance = 5;
	static const int worldHeight = 128;
	static const int chunkSize = 16;
	static const int columnHeight = worldHeight / chunkSize;
	static const int voxelToUUFactor = 100;
};
