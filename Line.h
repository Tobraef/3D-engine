#pragma once
#include "Point.h"
#include <vector>
#include "SFML\Graphics.hpp"
#include "SFML\Window.hpp"
class Line 
{
protected:
	std::pair<std::shared_ptr<Point>, std::shared_ptr<Point>> points;
	const sf::Color color = sf::Color::Red;
	sf::VertexArray drawableLine;
	void updateDrawable();
public:
	Line(std::shared_ptr<Point>&, std::shared_ptr<Point>&);
	Line() = default;
	Line(const Line&);
	Line& operator = (const Line& line)
	{
		points = line.points;
		drawableLine = line.drawableLine;
		return *this;
	}
	virtual ~Line();
	const float length;
	void move();
	std::pair <std::shared_ptr<Point>, std::shared_ptr<Point>> getPair() const;
	void draw(sf::RenderWindow &);
};

