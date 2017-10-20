#include "BlockStone.h"

FVector2D FBlockStone::texturePosition(Direction dir) {
	return FVector2D(1, 0);
}

bool FBlockStone::isSolid(Direction dir) {
	return true;
}