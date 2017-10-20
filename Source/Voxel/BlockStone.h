#pragma once

#include "CoreMinimal.h"
#include "Block.h"
#include "BlockStone.generated.h"

USTRUCT()
struct VOXEL_API FBlockStone : public FBlock
{
	GENERATED_USTRUCT_BODY()

protected:
	FVector2D texturePosition(Direction dir);
	bool isSolid(Direction dir);
};
