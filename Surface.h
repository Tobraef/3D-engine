#pragma once
#include "Line.h"
#include "Point.h"
#include "RotationAxis.h"
#include "Position.h"
class Surface : public Position
{ 
	sf::ConvexShape drawableSurface;
	std::vector<std::shared_ptr<Point>> points;
	std::vector<Line> lines;
	const sf::Color color = sf::Color::Green;
	void updateDrawable();
public:
	Surface(std::vector<std::shared_ptr<Point>>&, float, float, float);
	Surface(const Surface&);
	Surface& operator = (const Surface& o)
	{
		points = o.points;
		lines = o.lines;
		drawableSurface = o.drawableSurface;
		return *this;
	}
	~Surface();
	void draw(sf::RenderWindow &);
	void setRotation(const RotationAxis&);
	void move();
	std::vector<std::shared_ptr<Point>> getPoints();
	bool operator < (const Surface& s)
	{
		float thisMaxZ = points.front()->z;
		float maxZ = s.points.front()->z;
		for (auto& item : points)
		if (item->z > thisMaxZ)
			thisMaxZ = item->z;
		for (auto& item : s.points)
		if (item->z > maxZ)
			maxZ = item->z;
		return thisMaxZ < maxZ;
	}
};

