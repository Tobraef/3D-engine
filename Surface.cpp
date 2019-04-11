#include "Surface.h"


Surface::Surface(std::vector<std::shared_ptr<Point>>& ps, float x=0, float y=0, float z =0)
: Position(x,y,z)
{
	points = std::vector<std::shared_ptr<Point>>(ps);
	//Connects two points, then another two points, at last connects last points with first one
	for (unsigned int i = 0; i < points.size()-1; ++i)
	{
		lines.push_back(Line(points[i], points[i + 1]));
	}
	lines.push_back(Line(points[points.size() - 1], (points.front())));
	drawableSurface = sf::ConvexShape(points.size());
	for (unsigned int i = 0; i < points.size(); ++i)
	{
		drawableSurface.setPoint(i, sf::Vector2f(points[i]->xCast, points[i]->yCast));
	}
	drawableSurface.setFillColor(color);
}
Surface::Surface(const Surface& o)
: Position(o.x, o.y, o.z)
{
	points = o.points;
	lines = o.lines;
	drawableSurface = o.drawableSurface;
}
Surface::~Surface()
{
}
void Surface::draw(sf::RenderWindow & window)
{
	updateDrawable();
	//window.draw(drawableSurface);
	for (auto& item : lines)
		item.draw(window);
}
void Surface::updateDrawable()
{
	for (unsigned int i = 0; i < points.size(); ++i)
	{
		drawableSurface.setPoint(i, sf::Vector2f(points[i]->xCast, points[i]->yCast));
	}
}
void Surface::move()
{ 
	for (auto& item : points)
		item->move();
}
void Surface::setRotation(const RotationAxis& axis)
{
	for (auto& item : points)
		item->setRotation(axis.rotationCenterForPoint(*item), axis.getVector());
}
std::vector<std::shared_ptr<Point>> Surface::getPoints()
{
	return points;
}

