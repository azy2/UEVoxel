#include "TerrainGen.h"
#include "Chunk.h"
#include "Block.h"
#include "WorldManager.h"
#include "BlockStone.h"
#include "BlockGrass.h"
#include "BlockAir.h"

FTerrainGen::FTerrainGen() {
	noise = FastNoiseSIMD::NewFastNoiseSIMD();
	noise->SetNoiseType(FastNoiseSIMD::Simplex);
	worldHeight = AWorldManager::worldHeight;
	worldMinHeight = -worldHeight / 2;
	worldMaxHeight = worldHeight / 2;

	stoneBase = 0;
	stoneHeight = worldHeight / 6;
	stoneFrequency = .7;
	dirtBase = 1;
	dirtHeight = 3;
	dirtFrequency = .1;
	mountainBase = worldMinHeight;
	mountainHeight = worldHeight - (stoneBase + stoneHeight + dirtBase + dirtHeight );
	mountainFrequency = .3;
}

FTerrainGen::~FTerrainGen() {
	delete noise;
}

int FTerrainGen::scaleNoise(float noise, int max) {
	return (noise + 1.0f) * (max / 2.0f);
}

void FTerrainGen::chunkColumnGen(int x, int y, float mountainNoise, float stoneNoise, float dirtNoise, AChunk* chunk) {
	int stone = mountainBase;
	stone += scaleNoise(mountainNoise, mountainHeight);
	stone += stoneBase + scaleNoise(stoneNoise, stoneHeight);
	int dirt = stone + dirtBase + scaleNoise(dirtNoise, dirtHeight);
	for (int z = chunk->pos.Z; z < chunk->pos.Z + AChunk::chunkSize; ++z) {
		if (z <= stone) {
			setBlock(x, y, z, new FBlockStone(), chunk);
		}
		else if (z <= dirt) {
			setBlock(x, y, z, new FBlockGrass(), chunk);
		}
		else {
			setBlock(x, y, z, new FBlockAir(), chunk);
		}
	}
}

void FTerrainGen::chunkGen(AChunk* chunk) {
	float* mountainNoise = noise->GetSimplexSet(
		chunk->pos.X - 3, 
		chunk->pos.Y - 3, 
		0, 
		AChunk::chunkSize + 6, 
		AChunk::chunkSize + 6, 
		1,
		mountainFrequency);
	float* stoneNoise = noise->GetSimplexSet(
		chunk->pos.X - 3, 
		chunk->pos.Y - 3, 
		0, 
		AChunk::chunkSize + 6, 
		AChunk::chunkSize + 6, 
		1,
		stoneFrequency);
	float* dirtNoise = noise->GetSimplexSet(
		chunk->pos.X - 3, 
		chunk->pos.Y - 3, 
		0, 
		AChunk::chunkSize + 6, 
		AChunk::chunkSize + 6, 
		1,
		dirtFrequency);
	int i = 0;
	for (int x = chunk->pos.X - 3; x < chunk->pos.X + AChunk::chunkSize + 3; ++x) {
		for (int y = chunk->pos.Y - 3; y < chunk->pos.Y + AChunk::chunkSize + 3; ++y) {
			chunkColumnGen(x, y, mountainNoise[i], stoneNoise[i], dirtNoise[i], chunk);
			i++;
		}
	}
}

void FTerrainGen::setBlock(int x, int y, int z, FBlock* block, AChunk* chunk, bool replaceBlocks) {
	FIntVector v = FIntVector(x, y, z) - chunk->pos;
	if (chunk->inRange(v)) {
		if (replaceBlocks || chunk->getBlock(v) == NULL) {
			chunk->setBlock(v, block);
		}
	}
}