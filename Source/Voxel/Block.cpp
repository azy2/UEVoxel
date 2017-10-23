// Fill out your copyright notice in the Description page of Project Settings.

#include "Block.h"
#include "Chunk.h"
#include "SettingsManager.h"

FIntVector FBlock::directionToVector(Direction dir) {
	switch (dir) {
	case North:
		return FIntVector(0, 1, 0);
	case East:
		return FIntVector(1, 0, 0);
	case South:
		return FIntVector(0, -1, 0);
	case West:
		return FIntVector(-1, 0, 0);
	case Up:
		return FIntVector(0, 0, 1);
	case Down:
		return FIntVector(0, 0, -1);
	default:
		return FIntVector(0, 0, 0);
	}
}

Direction FBlock::oppositeDirection(Direction dir) {
	switch (dir) {
	case North:
		return South;
	case South:
		return North;
	case West:
		return East;
	case East:
		return West;
	case Up:
		return Down;
	case Down:
		return Up;
	default:
		return Up;
	}
}

void FBlock::blockData(AChunk* chunk, FIntVector pos, FMeshData* meshData) {
	meshData->useRenderDataForCol = true;
	for (int dir = North; dir <= Down; dir++) {
		FIntVector v = directionToVector((Direction) dir) + pos;
		FBlock* b = chunk->getBlock(v);
		if (b != NULL && !b->isSolid(oppositeDirection((Direction) dir))) {
			faceData((Direction) dir, chunk, pos, meshData);
		}
	}
}

void FBlock::faceData(Direction dir, AChunk* chunk, FIntVector &pos, FMeshData* meshData) {
	int s = USettingsManager::voxelToUUFactor;
	int b = s / 2;
	switch (dir) {
	case North:
		meshData->addVertex(FVector(pos.X * s + b, pos.Y * s + b, pos.Z * s - b));
		meshData->addVertex(FVector(pos.X * s + b, pos.Y * s + b, pos.Z * s + b));
		meshData->addVertex(FVector(pos.X * s - b, pos.Y * s + b, pos.Z * s + b));
		meshData->addVertex(FVector(pos.X * s - b, pos.Y * s + b, pos.Z * s - b));
		break;
	case East:
		meshData->addVertex(FVector(pos.X * s + b, pos.Y * s - b, pos.Z * s - b));
		meshData->addVertex(FVector(pos.X * s + b, pos.Y * s - b, pos.Z * s + b));
		meshData->addVertex(FVector(pos.X * s + b, pos.Y * s + b, pos.Z * s + b));
		meshData->addVertex(FVector(pos.X * s + b, pos.Y * s + b, pos.Z * s - b));
		break;
	case South:
		meshData->addVertex(FVector(pos.X * s - b, pos.Y * s - b, pos.Z * s - b));
		meshData->addVertex(FVector(pos.X * s - b, pos.Y * s - b, pos.Z * s + b));
		meshData->addVertex(FVector(pos.X * s + b, pos.Y * s - b, pos.Z * s + b));
		meshData->addVertex(FVector(pos.X * s + b, pos.Y * s - b, pos.Z * s - b));
		break;
	case West:
		meshData->addVertex(FVector(pos.X * s - b, pos.Y * s + b, pos.Z * s - b));
		meshData->addVertex(FVector(pos.X * s - b, pos.Y * s + b, pos.Z * s + b));
		meshData->addVertex(FVector(pos.X * s - b, pos.Y * s - b, pos.Z * s + b));
		meshData->addVertex(FVector(pos.X * s - b, pos.Y * s - b, pos.Z * s - b));
		break;
	case Up:
		meshData->addVertex(FVector(pos.X * s - b, pos.Y * s + b, pos.Z * s + b));
		meshData->addVertex(FVector(pos.X * s + b, pos.Y * s + b, pos.Z * s + b));
		meshData->addVertex(FVector(pos.X * s + b, pos.Y * s - b, pos.Z * s + b));
		meshData->addVertex(FVector(pos.X * s - b, pos.Y * s - b, pos.Z * s + b));
		break;
	case Down:
		meshData->addVertex(FVector(pos.X * s - b, pos.Y * s - b, pos.Z * s - b));
		meshData->addVertex(FVector(pos.X * s + b, pos.Y * s - b, pos.Z * s - b));
		meshData->addVertex(FVector(pos.X * s + b, pos.Y * s + b, pos.Z * s - b));
		meshData->addVertex(FVector(pos.X * s - b, pos.Y * s + b, pos.Z * s - b));
		break;
	default:
		return;
	}
	meshData->addQuadTriangles();
	faceUVs(dir, meshData);
}

void FBlock::faceUVs(Direction dir, FMeshData* meshData) {
	FVector2D tilePos = texturePosition(dir);
	meshData->UVs.Add(FVector2D(tileSize * tilePos.X, tileSize * tilePos.Y + tileSize));
	meshData->UVs.Add(FVector2D(tileSize * tilePos.X, tileSize * tilePos.Y));
	meshData->UVs.Add(FVector2D(tileSize * tilePos.X + tileSize, tileSize * tilePos.Y));
	meshData->UVs.Add(FVector2D(tileSize * tilePos.X + tileSize, tileSize * tilePos.Y + tileSize));
}

FVector2D FBlock::texturePosition(Direction dir) {
	return FVector2D();
}

bool FBlock::isSolid(Direction dir) {
	return false;
}

bool FBlock::isWater() {
	return false;
}

bool FBlock::isAir() {
	return false;
}