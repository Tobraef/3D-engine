#include "Line.h"

Line::Line(std::shared_ptr<Point>& p1, std::shared_ptr<Point>& p2) :
points(p1,p2),
length(sqrt(p1->x - p2->x)*(p1->x - p2->x) + (p1->y - p2->y)*(p1->y - p2->y) + (p1->z - p2->z)*(p1->z - p2->z))
{
	drawableLine = sf::VertexArray(sf::PrimitiveType::LinesStrip, 2);
	drawableLine[0].position = sf::Vector2f(p1->xCast, p1->yCast);
	drawableLine[1].position = sf::Vector2f(p2->xCast, p2->yCast);
	drawableLine[0].color = color;
	drawableLine[1].color = color;
}

Line::Line(const Line& line)
: points(line.points.first , line.points.second),
length(line.length)
{
	drawableLine = line.drawableLine;
}

Line::~Line()
{
}

void Line::move()
{
	points.first->move();
	points.second->move();
}
void Line::updateDrawable()
{
	drawableLine[0].position.x = points.first->xCast;
	drawableLine[0].position.y = points.first->yCast;
	drawableLine[1].position.x = points.second->xCast;
	drawableLine[1].position.y = points.second->yCast;
}
void Line::draw(sf::RenderWindow & window) 
{
	updateDrawable();
	window.draw(drawableLine);
}
std::pair < std::shared_ptr<Point>, std::shared_ptr<Point >> Line::getPair() const
{
	return points;
}