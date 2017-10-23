#pragma once

#include "CoreMinimal.h"
#include "Class.h"
#include "Block.generated.h"

struct FMeshData;
	
enum Direction {
	North,
	East,
	South,
	West,
	Up,
	Down
};

USTRUCT()
struct VOXEL_API FBlock
{
	GENERATED_USTRUCT_BODY()

protected:
	virtual bool isSolid(Direction dir);
	virtual FVector2D texturePosition(Direction dir);
	virtual void faceData(Direction dir, class AChunk *chunk, FIntVector &pos, FMeshData* meshData);
	virtual void faceUVs(Direction dir, FMeshData *meshData);
	FIntVector directionToVector(Direction dir);
	UPROPERTY()
	float tileSize = 0.0625f;
public:
	virtual bool isWater();
	virtual bool isAir();
	virtual void blockData(class AChunk* chunk, FIntVector pos, FMeshData* meshData);
private:
	Direction oppositeDirection(Direction dir);
};
