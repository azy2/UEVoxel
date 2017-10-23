#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Block.h"
#include "BlockWater.generated.h"

USTRUCT()
struct VOXEL_API FBlockWater : public FBlock
{
	GENERATED_BODY()
	
protected:
	bool isSolid(Direction dir);
	void faceData(Direction dir, class AChunk *chunk, FIntVector &pos, FMeshData* meshData);
	void faceUVs(Direction dir, FMeshData* meshData);
public:
	bool isWater();
	
};
