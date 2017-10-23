#include "WorldManager.h"
#include "math.h"
#include "BlockAir.h"
#include "ChunkLoader.h"
#include "SettingsManager.h"
#include "TerrainGen.h"
#include "Async.h"
#include "GameFramework/Actor.h"

// Sets default values
AWorldManager::AWorldManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	terrainGenSeed = FMath::Rand();
}

// Called when the game starts or when spawned
void AWorldManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWorldManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FIntVector AWorldManager::floorToChunkSpace(FIntVector pos) {
	FVector v = ((FVector) pos / (float) USettingsManager::chunkSize);
	FIntVector worldPos = FIntVector(
		floor(v.X) * USettingsManager::chunkSize, 
		floor(v.Y) * USettingsManager::chunkSize, 
		floor(v.Z) * USettingsManager::chunkSize);
	return worldPos;
}

void AWorldManager::createChunk(FIntVector pos) {
	FIntVector worldPos = floorToChunkSpace(pos);
	if (chunks.Contains(worldPos)) {
		return;
	}
	FVector uuPos = (FVector)worldPos * USettingsManager::voxelToUUFactor;
	AChunk* chunk = (AChunk*)GetWorld()->SpawnActor<AChunk>(AChunk::StaticClass(), uuPos, FRotator::ZeroRotator, FActorSpawnParameters());
	chunk->pos = worldPos;
	chunk->worldManager = this;

	(new FAutoDeleteAsyncTask<FTerrainGen>(chunk, terrainGenSeed))->StartBackgroundTask();
	chunks.Add(worldPos, chunk);
}

void AWorldManager::destroyChunk(FIntVector pos) {
	FIntVector worldPos = floorToChunkSpace(pos);
	if (chunks.Contains(worldPos)) {
		chunks[worldPos]->K2_DestroyActor();
		chunks[worldPos] = NULL;
		chunks.Remove(worldPos);
	}
}

AChunk* AWorldManager::getChunk(FIntVector pos) {
	FIntVector worldPos = floorToChunkSpace(pos);
	if (!chunks.Contains(worldPos)) {
		return NULL;
	}
	else {
		return chunks[worldPos];
	}
}

FBlock* AWorldManager::getBlock(FIntVector pos) {
	static FBlock* offWorldBlock = new FBlockAir();
	AChunk* containerChunk = getChunk(pos);
	if (containerChunk != NULL) {
		return containerChunk->getBlock(pos - containerChunk->pos);
	}
	else {
		return offWorldBlock;
	}
}

void AWorldManager::setBlock(FIntVector pos, FBlock* block) {
	AChunk* containerChunk = getChunk(pos);
	if (containerChunk != NULL) {
		containerChunk->setBlock(pos - containerChunk->pos, block);
		containerChunk->needsUpdate();
	}
}

void AWorldManager::destroyBlock(FIntVector pos) {
	AChunk* containerChunk = getChunk(pos);
	if (containerChunk != NULL) {
		containerChunk->destroyBlock(pos - containerChunk->pos);
		containerChunk->needsUpdate();
	}
}