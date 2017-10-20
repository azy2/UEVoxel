#pragma once

#include "CoreMinimal.h"
#include "Block.h"
#include "BlockGrass.generated.h"

USTRUCT()
struct VOXEL_API FBlockGrass : public FBlock
{
	GENERATED_USTRUCT_BODY()

protected:
	FVector2D texturePosition(Direction dir);
	bool isSolid(Direction dir);
};