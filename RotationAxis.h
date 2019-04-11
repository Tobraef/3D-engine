#pragma once
#include "Line.h"
//class specified for calculating the rotation center and radius for a specified point, that wants to rotate around the axis
class RotationAxis :
	public Line
{
	Position vector;
public:
	RotationAxis(std::shared_ptr<Point>&, std::shared_ptr<Point>&);
	~RotationAxis();
	Position rotationCenterForPoint(const Point&) const;
	Position getVector() const;
};

