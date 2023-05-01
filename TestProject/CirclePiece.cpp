#include "CirclePiece.h"

CirclePiece::CirclePiece(SDL_FPoint pPosition, SDL_FPoint pSecondaryPosition, float pWidth, float pDeviationAngle, float pStiffness)
	: position(pPosition), secondaryPosition(pSecondaryPosition), width(pWidth), deviationAngle(pDeviationAngle), stiffness(pStiffness)
{
	radius = width / 2;
	hitboxCenter = { position.x - ((position.x - secondaryPosition.x) / 2), position.y - ((position.y - secondaryPosition.y) / 2) };
	speed = 0;
	shift = 0;
	shiftVector = {0, 0};
}
