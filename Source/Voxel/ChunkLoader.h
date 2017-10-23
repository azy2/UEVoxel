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
	UPROPERTY()
	AWorldManager* worldManager;
	UPROPERTY()
	TArray<FIntVector> updateList;
	UPROPERTY()
	TArray<FIntVector> buildList;
	UPROPERTY()
	TArray<FIntVector> deleteList;
public:
	void setWorldManager(AWorldManager* worldManager);
	void findChunksToLoad(FVector uuPlayerPos);
	void loadAndRenderChunks();
	void buildChunk(FIntVector pos);
	void deleteChunks(FVector uuPlayerPos, UWorld* world);
};
