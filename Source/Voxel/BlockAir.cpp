#include "BlockAir.h"

void FBlockAir::blockData(AChunk* chunk, FIntVector pos, FMeshData* meshData) {
	return;
}

FVector2D FBlockAir::texturePosition(Direction dir) {
	return FVector2D();
}

bool FBlockAir::isSolid(Direction dir) {
	return false;
}