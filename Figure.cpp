#include "Figure.h"


Figure::Figure(std::vector<Surface>& surfaces)
: surfaces(surfaces)
{
	for (auto& surface : surfaces)
	{
		std::vector<std::shared_ptr<Point>> & pointsVector = surface.getPoints();
		for (auto& item : pointsVector)
			points.insert(item);
	}
	std::sort(surfaces.begin(), surfaces.end());
}

Figure::~Figure()
{
}

void Figure::move()
{
	for (auto& item : surfaces)
		item.move();
}
void Figure::draw(sf::RenderWindow& window)
{
	//sorting, so that those above the others, are drawn last. Currently not really working
	//std::sort(surfaces.begin(), surfaces.end());
	for (auto& item : surfaces)
		item.draw(window);
}
void Figure::setRotation(RotationAxis& axis)
{
	for (auto& item : points)
		item->setRotation(axis.rotationCenterForPoint(*item), axis.getVector());
}