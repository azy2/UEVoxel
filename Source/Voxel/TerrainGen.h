#pragma once

#include "CoreMinimal.h"
#include "AsyncWork.h"

class VOXEL_API FTerrainGen : public FNonAbandonableTask
{
	friend class FAutoDeleteAsyncTask<FTerrainGen>;

public:
	FTerrainGen(class AChunk* chunk, int seed);
	~FTerrainGen();
private:
	void chunkGen();
	void setBlock(int x, int y, int z, struct FBlock* block, class AChunk* chunk, bool replaceBlocks = false);
	int scaleNoise(float noise, int max);
	class FastNoiseSIMD* noise;
	class AChunk* chunk;

protected:
	void DoWork();
	FORCEINLINE TStatId GetStatId() const {
		RETURN_QUICK_DECLARE_CYCLE_STAT(FTerrainGen, STATGROUP_ThreadPoolAsyncTasks);
	}
};
