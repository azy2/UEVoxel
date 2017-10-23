#include "BlockWater.h"
#include "SettingsManager.h"
#include "MeshData.h"
#include "Chunk.h"

bool FBlockWater::isSolid(Direction dir) {
	return false;
}

bool FBlockWater::isWater() {
	return true;
}

void FBlockWater::faceData(Direction dir, AChunk* chunk, FIntVector& pos, FMeshData* meshData) {
	if (dir == Up) {
		int s = USettingsManager::voxelToUUFactor;
		int b = s / 2;
		FIntVector v = directionToVector(Up) + pos;
		FBlock* block = chunk->getBlock(v);
		if (b && block->isAir()) {
			meshData->addVertex(FVector(pos.X * s - b, pos.Y * s + b, pos.Z * s + b));
			meshData->addVertex(FVector(pos.X * s + b, pos.Y * s + b, pos.Z * s + b));
			meshData->addVertex(FVector(pos.X * s + b, pos.Y * s - b, pos.Z * s + b));
			meshData->addVertex(FVector(pos.X * s - b, pos.Y * s - b, pos.Z * s + b));
			meshData->addQuadTriangles();
			faceUVs(dir, meshData);
		}
	}
}

void FBlockWater::faceUVs(Direction dir, FMeshData* meshData) {
	FVector2D tilePos = texturePosition(dir);
	meshData->UVs.Add(FVector2D(tilePos.X, tilePos.Y + 1));
	meshData->UVs.Add(FVector2D(tilePos.X, tilePos.Y));
	meshData->UVs.Add(FVector2D(tilePos.X + 1, tilePos.Y));
	meshData->UVs.Add(FVector2D(tilePos.X + 1, tilePos.Y + 1));
}