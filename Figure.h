#pragma once
#include "Surface.h"
#include <set>
class Figure
{
	std::vector<Surface> surfaces;
	std::set<std::shared_ptr<Point>> points;
public:
	Figure(std::vector<Surface>&);
	void draw(sf::RenderWindow&);
	void setRotation(RotationAxis&);
	void move();
	~Figure();
};

