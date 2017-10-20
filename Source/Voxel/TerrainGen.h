#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FastNoiseSIMD.h"
#include "TerrainGen.generated.h"

USTRUCT()
struct VOXEL_API FTerrainGen
{
	GENERATED_USTRUCT_BODY()

private:
	FastNoiseSIMD* noise;
	UPROPERTY()
	int worldHeight;
	UPROPERTY()
	int worldMinHeight;
	UPROPERTY()
	int worldMaxHeight;
public:
	FTerrainGen();
	~FTerrainGen();
	void chunkGen(class AChunk* chunk);
	void chunkColumnGen(int x, int y, float mountainNoise, float stoneNoise, float dirtNoise, class AChunk* chunk);
	void setBlock(int x, int y, int z, struct FBlock* block, class AChunk* chunk, bool replaceBlocks = false);
	int scaleNoise(float noise, int max);
private:
	int stoneBase;
	int stoneHeight;
	float stoneFrequency;
	int mountainBase;
	int mountainHeight;
	float mountainFrequency;
	int dirtBase;
	int dirtHeight;
	float dirtFrequency;
};
