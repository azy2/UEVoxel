#include "ChunkLoader.h"
#include "Chunk.h"
#include "SettingsManager.h"
#include "math.h"

void FChunkLoader::setWorldManager(AWorldManager* _worldManager) {
	worldManager = _worldManager;
}

void FChunkLoader::findChunksToLoad(FVector uuPlayerPosition) {
		FIntVector playerPos = FIntVector(
			(int)floor(uuPlayerPosition.X / USettingsManager::voxelToUUFactor / (float) USettingsManager::chunkSize) * USettingsManager::chunkSize,
			(int)floor(uuPlayerPosition.Y / USettingsManager::voxelToUUFactor / (float) USettingsManager::chunkSize) * USettingsManager::chunkSize,
			(int)floor(uuPlayerPosition.Z / USettingsManager::voxelToUUFactor / (float) USettingsManager::chunkSize) * USettingsManager::chunkSize);
		for (int x = -USettingsManager::viewDistance; x <= USettingsManager::viewDistance; x++) {
			for (int y = -USettingsManager::viewDistance; y <= USettingsManager::viewDistance; y++) {
				for (int z = -USettingsManager::viewDistance; z <= USettingsManager::viewDistance; z++) {
					FIntVector newChunkPos = FIntVector(x, y, z) * USettingsManager::chunkSize + playerPos;

					AChunk* newChunk = worldManager->getChunk(newChunkPos);

					if (newChunk != NULL) {
						continue;
					}

					buildList.Add(newChunkPos);
				}
			}
		}
}

void FChunkLoader::loadAndRenderChunks() {
	for (int i = 0; i < 16 && buildList.Num() != 0; i++) {
		buildChunk(buildList.Pop());
	}
}

void FChunkLoader::buildChunk(FIntVector pos) {
	if (worldManager->getChunk(pos) == NULL) {
		worldManager->createChunk(pos);
	}
}

void FChunkLoader::deleteChunks(FVector uuPlayerPos, UWorld* world) {
		uuPlayerPos /= (float)USettingsManager::voxelToUUFactor;
		for (auto pair : worldManager->chunks) {
        if ((int)abs(((int)uuPlayerPos.X - pair.Key.X)) / USettingsManager::chunkSize > USettingsManager::viewDistance + 1 ||
            (int)abs(((int)uuPlayerPos.Y - pair.Key.Y)) / USettingsManager::chunkSize > USettingsManager::viewDistance + 1 ||
            (int)abs(((int)uuPlayerPos.Z - pair.Key.Z)) / USettingsManager::chunkSize > USettingsManager::viewDistance + 1) {
            worldManager->destroyChunk(pair.Key);
			}
		}
    world->ForceGarbageCollection(true);
}
