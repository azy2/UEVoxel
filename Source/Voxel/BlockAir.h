#pragma once

#include "CoreMinimal.h"
#include "Class.h"
#include "Block.h"
#include "BlockAir.generated.h"

USTRUCT()
struct VOXEL_API FBlockAir : public FBlock
{
	GENERATED_USTRUCT_BODY()

public:
	void blockData(AChunk* chunk, FIntVector pos, FMeshData* meshData);
	bool isAir();
protected:
	FVector2D texturePosition(Direction dir);
	bool isSolid(Direction dir);
};
