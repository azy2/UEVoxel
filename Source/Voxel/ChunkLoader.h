#pragma once

#include "CoreMinimal.h"
#include "WorldManager.h"
#include "Containers/Queue.h"
#include "UObject/NoExportTypes.h"
#include "Class.h"
#include "ChunkLoader.generated.h"

USTRUCT()
struct VOXEL_API FChunkLoader
{
	GENERATED_USTRUCT_BODY()

private:
	// TODO: Move this?
	UPROPERTY()
	int viewDistance = 3;
	UPROPERTY()
	AWorldManager* worldManager;
	UPROPERTY()
	TArray<FIntVector> updateList;
	UPROPERTY()
	TArray<FIntVector> buildList;
public:
	void setWorldManager(AWorldManager* worldManager);
	void findChunksToLoad(FVector uuPlayerPos);
	void loadAndRenderChunks();
	void buildChunk(FIntVector pos);
	void deleteChunks(FVector uuPlayerPos, UWorld* world);
};
