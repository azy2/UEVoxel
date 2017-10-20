#include "ChunkLoader.h"
#include "Chunk.h"
#include "math.h"

void FChunkLoader::setWorldManager(AWorldManager* _worldManager) {
	worldManager = _worldManager;
}

void FChunkLoader::findChunksToLoad(FVector uuPlayerPosition) {
	if (buildList.Num() == 0) {
		FIntVector playerPos = FIntVector(
			(int)floor(uuPlayerPosition.X / 100.0f / (float) AChunk::chunkSize) * AChunk::chunkSize,
			(int)floor(uuPlayerPosition.Y / 100.0f / (float) AChunk::chunkSize) * AChunk::chunkSize,
			(int)floor(uuPlayerPosition.Z / 100.0f / (float) AChunk::chunkSize) * AChunk::chunkSize);
		for (int x = -viewDistance; x <= viewDistance; x++) {
			for (int y = -viewDistance; y <= viewDistance; y++) {
				FIntVector newChunkPos = FIntVector(x, y, 0) * AChunk::chunkSize + playerPos;
				newChunkPos.Z = 0; // The player is rarely at 0

				AChunk* newChunk = worldManager->getChunk(newChunkPos);

				if (newChunk != NULL && (newChunk->isRendered() || updateList.Contains(newChunkPos))) {
					continue;
				}

				for (int z = -worldManager->columnHeight / 2; z < worldManager->columnHeight / 2; z++) {
					for (int xx = newChunkPos.X - AChunk::chunkSize; xx <= newChunkPos.X + AChunk::chunkSize; xx += AChunk::chunkSize) {
						for (int yy = newChunkPos.Y - AChunk::chunkSize; yy <= newChunkPos.Y + AChunk::chunkSize; yy += AChunk::chunkSize) {
							buildList.Add(FIntVector(xx, yy, z * AChunk::chunkSize));
						}
					}
					updateList.Add(FIntVector(newChunkPos.X, newChunkPos.Y, z * AChunk::chunkSize));
				}

				return;
			}
		}
	}
}

void FChunkLoader::loadAndRenderChunks() {
	while (buildList.Num() != 0) {
		buildChunk(buildList.Pop());
	}
	return;
	while (updateList.Num() != 0) {
		AChunk* chunk = worldManager->getChunk(updateList[0]);
		if (chunk != NULL) {
			chunk->needsUpdate();
		}
		updateList.RemoveAt(0);
	}
}

void FChunkLoader::buildChunk(FIntVector pos) {
	if (worldManager->getChunk(pos) == NULL) {
		worldManager->createChunk(pos);
	}
}

void FChunkLoader::deleteChunks(FVector uuPlayerPos, UWorld* world) {
	static int delteTimer = 0;
	if (delteTimer == 60) {
		uuPlayerPos.Z = 0;
		uuPlayerPos /= 100.0f;
		for (auto pair : worldManager->chunks) {
			float distance = FVector::Dist(uuPlayerPos, FVector(pair.Key.X, pair.Key.Y, 0));
			float t = (viewDistance + 1) * AChunk::chunkSize;
			if (distance > sqrt(t*t + t*t)) {
				worldManager->destroyChunk(pair.Key);
			}
		}
		delteTimer = 0;
		world->ForceGarbageCollection(true);
		return;
	}
	delteTimer++;
}