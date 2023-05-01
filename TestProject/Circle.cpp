#include "Circle.h"
extern SDL_Renderer* renderer;
extern float scaleX;
extern float scaleY;

Circle::Circle(Point pPosition, SDL_Texture* pTexture, SDL_Texture* pPiecesTexture, float pRadius, float speed, float pStiffness)
	: Actor(pPosition, int(pRadius) * 1.35, int(pRadius) * 1.35, pTexture)
{
	radius = pRadius;
	width = radius / 5;
	pieces = 32;
	stepDegree = TO_RADIANS(360 / float(pieces));

	setSomeSettingsToDefault();

	piecesTexture = pPiecesTexture;
	circlePieces.reserve(pieces);
	for (int i = 0; i < pieces; i++) {
		circlePieces.emplace_back(CirclePiece
			{ 
				SDL_FPoint{ position.x + (radius * cos(i * stepDegree)), position.y + (radius * sin(i * stepDegree)) },
				SDL_FPoint{ position.x + ((radius - width) * cos(i * stepDegree)), position.y + ((radius - width) * sin(i * stepDegree)) },
				width, 
				stepDegree * i, 
				pStiffness,
			});
	}
}

void Circle::setSomeSettingsToDefault()
{
	lastPosition = { 0, 0 };
	deltaDistance = 0;

	movementVector = { 0, 0 };
	speed = 0;
	acceleration = 1500;

	gravityVector = { 0, 1500 };
	airResistance = 1;

	rotationSpeed = 0;

	maxShift = 0;
	maxShiftPieceShiftVector = {0, 0};
}

float Circle::getRadius()
{
	return radius;
}

Point Circle::getPosition()
{
	return position;
}

void Circle::drawPieces() 
{
	SDL_Color circleColor = { 255, 255, 255, 255 };
	std::vector< SDL_Vertex > verts;

	for (int i = 0; i < pieces; i++) {
		if (i != pieces - 1) {
			 verts = {
				 /*{ circlePieces[i].position, circleColor, SDL_FPoint{0, 0},},
				 { circlePieces[i + 1].position, circleColor, SDL_FPoint{ 1, 0 }, },
				 { circlePieces[i].secondaryPosition, circleColor, SDL_FPoint{ 0, 1 }, },
				 { circlePieces[i].secondaryPosition, circleColor, SDL_FPoint{ 0, 1 }, },
				 { circlePieces[i + 1].secondaryPosition, circleColor, SDL_FPoint{ 1, 1 }, },
				 { circlePieces[i + 1].position, circleColor, SDL_FPoint{ 1, 0 }, },*/
				 { SDL_FPoint {position.x, position.y}, circleColor, SDL_FPoint{ 0.5, 0 },},
				 { circlePieces[i].position, circleColor, SDL_FPoint{ 1, 1 },},
				 { circlePieces[i + 1].position, circleColor, SDL_FPoint{ 0, 1 }, },
			};
		}
		else {
			verts = {
				 /*{ circlePieces[i].position, circleColor, SDL_FPoint{0, 0},},
				 { circlePieces[0].position, circleColor, SDL_FPoint{ 1, 0 }, },
				 { circlePieces[i].secondaryPosition, circleColor, SDL_FPoint{ 0, 1 }, },
				 { circlePieces[i].secondaryPosition, circleColor, SDL_FPoint{ 0, 1 }, },
				 { circlePieces[0].secondaryPosition, circleColor, SDL_FPoint{ 1, 1 }, },
				 { circlePieces[0].position, circleColor, SDL_FPoint{ 1, 0 }, },*/
				 { SDL_FPoint {position.x, position.y}, circleColor, SDL_FPoint{ 0.5, 0 },},
				 { circlePieces[i].position, circleColor, SDL_FPoint{ 1, 1 },},
				 { circlePieces[0].position, circleColor, SDL_FPoint{ 0, 1 }, },
			};
		}
		//scaling
		for (int i = 0; i < verts.size(); i++) {
			verts[i].position.x *= scaleX;
			verts[i].position.y *= scaleY;
		}

		SDL_RenderGeometry(renderer, piecesTexture, verts.data(), verts.size(), nullptr, 0);
	}
}

void Circle::goUp(float tickTime)
{
	movementVector.y -= acceleration * tickTime;
}

void Circle::goLeft(float tickTime)
{
	movementVector.x -= acceleration * tickTime;
}

void Circle::goDown(float tickTime)
{
	movementVector.y += acceleration * tickTime;
}

void Circle::goRight(float tickTime)
{
	movementVector.x += acceleration * tickTime;
}

void Circle::move(float tickTime) 
{
	lastPosition = position;
	position = position + (movementVector * tickTime);
	deltaDistance = calculateDistanceBetweenPoints(lastPosition, position);
	speed = vectorLength(movementVector);

	textureRectangle.x = int(position.x) - textureWidth / 2;
	textureRectangle.y = int(position.y) - textureHeight / 2;
}

void Circle::calculateRotationSpeed(float tickTime)
{
	Point linePointVector = calculateMovementVector({0, 0}, { -maxShiftPieceShiftVector.y, maxShiftPieceShiftVector.x });
	float distanceAlongTheLine = (movementVector.x * linePointVector.x + movementVector.y * linePointVector.y) * tickTime;

	float lastRotationSpeed = rotationSpeed;
	rotationSpeed = distanceAlongTheLine / (2 * PI * radius / 360) / 2;
	//calculateRotationReaction(tickTime, rotationSpeed - lastRotationSpeed, linePointVector);
}

void Circle::calculateRotationReaction(float tickTime, float deltaRotationSpeed, Point linePointVector)
{
	//movementVector = movementVector + (linePointVector * (-deltaRotationSpeed) * 1000);
}

void Circle::rotate()
{
	rotationAngle += rotationSpeed;
	arrangeThePieces();
}

void Circle::rotationSlowdown(float tickTime)
{
	if (rotationSpeed > 0 && rotationSpeed > ROTATION_SLOWDOWN * tickTime) {
		rotationSpeed -= ROTATION_SLOWDOWN * tickTime;
	}
	else if (rotationSpeed < 0 && rotationSpeed < ROTATION_SLOWDOWN * tickTime) {
		rotationSpeed += ROTATION_SLOWDOWN * tickTime;
	}
	else {
		rotationSpeed = 0;
	}
}

void Circle::arrangeThePieces()
{
	float angleInRadians = TO_RADIANS(rotationAngle);
	for (auto& piece : circlePieces) {
		piece.position = {
			position.x + ((radius - piece.shift) * cos(angleInRadians + piece.deviationAngle)),
			position.y + ((radius - piece.shift) * sin(angleInRadians + piece.deviationAngle))
		};
		piece.secondaryPosition = {
			position.x + ((radius - width - piece.shift) * cos(angleInRadians + piece.deviationAngle)),
			position.y + ((radius - width - piece.shift) * sin(angleInRadians + piece.deviationAngle))
		};
	}
}

void Circle::gravityEffect(float tickTime)
{
	movementVector = movementVector + (gravityVector * tickTime);
}

void Circle::calculateAirResistance(float tickTime)
{
	movementVector = movementVector * (1 - (airResistance * tickTime));
}

void Circle::calculateCollisions(Point lineP1, Point lineP2)
{
	float distanceFromCenterToLine = dotToLineDistance(position, lineP1, lineP2);
	float distanceToLine;
	float shiftDeltaDistance;
	int maxRadiusShiftCount;
	for (auto& piece : circlePieces) {
		shiftDeltaDistance = distanceFromCenterToLine - dotToLineDistance(position + (piece.shiftVector * (-piece.radius)), lineP1, lineP2);
		if (shiftDeltaDistance > 0) {
			maxRadiusShiftCount = radius / piece.radius;
			for (int i = 1; i < maxRadiusShiftCount; i++) {
				distanceToLine = dotToLineDistance(position + (piece.shiftVector * (-i) * piece.radius), lineP1, lineP2);
				if (distanceToLine < piece.radius) {
					piece.shift = radius - vectorLength(piece.shiftVector * (-i) * piece.radius) - distanceToLine;
					if (piece.shift > piece.lastShift) {
						piece.lastShift = piece.shift;
						if (piece.shift > maxShift) {
							maxShift = piece.shift;
							maxShiftPieceShiftVector = piece.shiftVector;
						}
					}
					else {
						piece.shift = piece.lastShift;
					}
				}
			}
		}
	}
}

void Circle::calculatePiecesShiftVectors()
{
	for (auto& piece : circlePieces) {
		piece.shiftVector = calculateMovementVector({ piece.position.x, piece.position.y }, position);
	}
}

void Circle::calculatePiecesResistance(float tickTime)
{
	for (auto& piece : circlePieces) {
		movementVector = movementVector + (piece.shiftVector * piece.shift * piece.shift * piece.stiffness  * (100 / radius) * (100 / radius) * tickTime);
	}
}

void Circle::piecesShiftReset()
{
	for (auto& piece : circlePieces) {
		piece.shift = 0;
		piece.lastShift = 0;
	}
	maxShift = 0;
}