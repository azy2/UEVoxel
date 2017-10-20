#include "BlockGrass.h"

FVector2D FBlockGrass::texturePosition(Direction dir) {
	switch (dir) {
	case Up:
		return FVector2D(0, 0);
	case Down:
		return FVector2D(2, 0);
	default:
		return FVector2D(3, 0);
	}
}

bool FBlockGrass::isSolid(Direction dir) {
	return true;
}