#pragma once
#include "Position.h"
class Observator :
	public Position
{
	Position directionVector;
	const float vectorLength;
	const float viewAngle = 1.57; //angle in radians
public:
	Observator(float = 600, float = 300, float = 400, float = 200);
	~Observator();
	void move(float, float, float);
	Position getDirectionVector() const;
	void rotateAround(float angle);
	void upLook(float angle);
};