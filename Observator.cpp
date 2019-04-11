#include "Observator.h"
#include <math.h>
#include <iostream>

Observator::Observator(float x, float y, float z, float distance)
: Position(x, y, z),
  directionVector(0,0,200),
  vectorLength(distance)
{
	
}

Observator::~Observator()
{
}

void Observator::move(float dx, float dy, float dz)
{
	x += dx;
	y += dy;
	z += dz;
}

Position Observator::getDirectionVector() const
{
	return directionVector;
}
void Observator::rotateAround(float angle)
{
	float fraction = sqrt(directionVector.x*directionVector.x + directionVector.z*directionVector.z);
	directionVector.x = directionVector.x*cos(angle) - directionVector.z*sin(angle);
	directionVector.z = directionVector.x*sin(angle) + directionVector.z*cos(angle);
	float change = sqrt(directionVector.x*directionVector.x + directionVector.z*directionVector.z);
	directionVector.x *= fraction / change;
	directionVector.z *= fraction / change;
}
void Observator::upLook(float angle)
{
	float vecVal = sqrt(directionVector.x*directionVector.x + directionVector.z*directionVector.z);
	float fr = sqrt(directionVector.y*directionVector.y + vecVal*vecVal);
	vecVal = vecVal*cos(angle) - directionVector.z*sin(angle);
	directionVector.y = vecVal*sin(angle) + directionVector.y*cos(angle);
	float change = sqrt(directionVector.y*directionVector.y + vecVal*vecVal);
	vecVal *= fr / change;
	directionVector.y *= fr / change;
	float fraction = directionVector.x / directionVector.z;
	if (directionVector.x == 0)
	{
		if (directionVector.z == 0)
		fraction = 1;
		else
		{
			directionVector.x = vecVal;
			return;
		}
	}
	directionVector.z = vecVal / sqrt(fraction*fraction + 1);
	directionVector.x = directionVector.z*fraction;
}