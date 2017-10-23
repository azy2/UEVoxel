#include "TerrainGen.h"
#include "FastNoiseSIMD.h"
#include "Chunk.h"
#include "Block.h"
#include "BlockStone.h"
#include "BlockGrass.h"
#include "BlockAir.h"
#include "BlockWater.h"
#include "math.h"

FTerrainGen::FTerrainGen(AChunk* _chunk, int seed) {
	chunk = _chunk;
	noise = FastNoiseSIMD::NewFastNoiseSIMD();
	noise->SetNoiseType(FastNoiseSIMD::Value);
	noise->SetSeed(seed);
}

FTerrainGen::~FTerrainGen() {
	delete noise;
}

int FTerrainGen::scaleNoise(float noise, int max) {
	return (noise + 1.0f) * (max / 2.0f);
}

void FTerrainGen::DoWork() {
	chunkGen();
}

void FTerrainGen::chunkGen() {
	float* noiseSet1 = noise->GetValueSet(
		chunk->pos.X,
		chunk->pos.Y,
		0,
		USettingsManager::chunkSize,
		USettingsManager::chunkSize,
		1,
		1.0f);
	float* noiseSet2 = noise->GetValueSet(
		chunk->pos.X,
		chunk->pos.Y,
		0,
		USettingsManager::chunkSize,
		USettingsManager::chunkSize,
		1,
		0.5f);
	float* noiseSet3 = noise->GetValueSet(
		chunk->pos.X,
		chunk->pos.Y,
		0,
		USettingsManager::chunkSize,
		USettingsManager::chunkSize,
		1,
		0.25f);
	int i = 0;
	for (int x = chunk->pos.X; x < chunk->pos.X + USettingsManager::chunkSize; ++x) {
		for (int y = chunk->pos.Y; y < chunk->pos.Y + USettingsManager::chunkSize; ++y) {
			float noiseSample1 = noiseSet1[i] * 0.25;
			float noiseSample2 = noiseSet2[i] * 0.5;
			float noiseSample3 = noiseSet3[i] * 1.0;
			i++;
			float noiseSample = noiseSample1 + noiseSample2 + noiseSample3 + 1.75;
			noiseSample = pow(noiseSample, 1.5);
			noiseSample = (noiseSample / pow(3.5, 1.5)) * USettingsManager::worldHeight - (USettingsManager::worldHeight / 2);
			for (int z = chunk->pos.Z; z < chunk->pos.Z + USettingsManager::chunkSize; ++z) {
				if (z <= noiseSample) {
					setBlock(x, y, z, new FBlockGrass(), chunk);
				}
				//else if (z <= -(3 * USettingsManager::worldHeight / 8)) {
				//	setBlock(x, y, z, new FBlockWater(), chunk);
				//}
				else {
					setBlock(x, y, z, new FBlockAir(), chunk);
				}
			}
		}
	}

	FastNoiseSIMD::FreeNoiseSet(noiseSet1);
	FastNoiseSIMD::FreeNoiseSet(noiseSet2);
	FastNoiseSIMD::FreeNoiseSet(noiseSet3);
	chunk->needsUpdate();
}

void FTerrainGen::setBlock(int x, int y, int z, FBlock* block, AChunk* chunk, bool replaceBlocks) {
	FIntVector v = FIntVector(x, y, z) - chunk->pos;
	if (chunk->inRange(v)) {
		if (replaceBlocks || chunk->getBlock(v) == NULL) {
			chunk->setBlock(v, block);
		}
	}
}