#include "Position.h"


Position::Position(const float& x,const float& y,const float& z)
: x(x), y(y), z(z)
{
}
Position::Position(const Position& p)
: x(p.x), y(p.y), z(p.z)
{
}
Position::~Position()
{
}

float Position::getX() const
{
	return x;
}
float Position::getY() const
{
	return y;
}
float Position::getZ() const
{
	return z;
}

void Position::setX(float x)
{
	this->x = x;
}
void Position::setY(float y)
{
	this->y = y;
}
void Position::setZ(float z)
{
	this->z = z;
}