#include "RotationAxis.h"


RotationAxis::RotationAxis(std::shared_ptr<Point>& p1, std::shared_ptr<Point>& p2) :
Line(p1, p2), vector(Position(p2->x - p1->x, p2->y - p1->y, p2->z - p1->z))
{
}

RotationAxis::~RotationAxis()
{
}

Position RotationAxis::rotationCenterForPoint(const Point& p) const
{
	float t = (vector.x*(p.x - points.first->x) + vector.y*(p.y - points.first->y) + vector.z*(p.z - points.first->z)) /
		(vector.x*vector.x + vector.y*vector.y + vector.z*vector.z);
	Position po(vector.x*t + points.first->x, vector.y*t + points.first->y, vector.z*t + points.first->z);
	return po;
}

Position RotationAxis::getVector() const
{
	return vector;
}