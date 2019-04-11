// Program_obrotowy.cpp : Defines the entry point for the console application.
//
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include "stdafx.h"
#include <vector>
#include "RotationAxis.h"
#include "Surface.h"
#include "windows.h"
#include "Figure.h"
void draw(std::vector<Figure> & f, sf::RenderWindow& window)
{
	window.clear();
	for (auto& item : f)
		item.draw(window);
	window.display();
}
int main()
{
	sf::RenderWindow window(sf::VideoMode(1200, 600), "Rotation");
	Observator observator(300,0,0,200);
	float mouseX = sf::Mouse::getPosition().x;
	float mouseY = sf::Mouse::getPosition().y;
	std::vector<std::shared_ptr<Point>> points;
	std::shared_ptr<Point> a(new Point(observator, 250, 0, 250));
	std::shared_ptr<Point> b(new Point(observator, 350, 0, 250));
	std::shared_ptr<Point> d(new Point(observator, 250, 0, 350));
	std::shared_ptr<Point> c(new Point(observator, 350, 0, 350));
	std::shared_ptr<Point> ah(new Point(observator, 250, 50, 250));
	std::shared_ptr<Point> bh(new Point(observator, 350, 50, 250));
	std::shared_ptr<Point> dh(new Point(observator, 250, 50, 350));
	std::shared_ptr<Point> ch(new Point(observator, 350, 50, 350));
	Figure figure(std::vector<Surface> {Surface(std::vector<std::shared_ptr<Point>>{a, b, c, d}, 0,0,0)
		, Surface(std::vector<std::shared_ptr<Point>>{ah, bh, ch, dh}, 0, 0, 0)
		, Surface(std::vector<std::shared_ptr<Point>>{a, b, bh, ah}, 0, 0, 0)
		, Surface(std::vector<std::shared_ptr<Point>>{b, c, ch, bh}, 0, 0, 0)
		, Surface(std::vector<std::shared_ptr<Point>>{c, d, dh, ch}, 0, 0, 0)
		, Surface(std::vector<std::shared_ptr<Point>>{d, a, ah, dh}, 0, 0, 0)});
	/*std::shared_ptr<Point> x(new Point(observator, 850, 250, -50));
	std::shared_ptr<Point> y(new Point(observator, 950, 250, -50));
	std::shared_ptr<Point> w(new Point(observator, 850, 350, -50));
	std::shared_ptr<Point> z(new Point(observator, 950, 350, -50));
	std::shared_ptr<Point> xh(new Point(observator, 850, 250, 100));
	std::shared_ptr<Point> yh(new Point(observator, 950, 250, 100));
	std::shared_ptr<Point> wh(new Point(observator, 850, 350, 100));
	std::shared_ptr<Point> zh(new Point(observator, 950, 350, 100));
	Figure figure2(std::vector<Surface> {Surface(std::vector<std::shared_ptr<Point>>{x, y, z, w})
		, Surface(std::vector<std::shared_ptr<Point>>{xh, yh, zh, wh})
		, Surface(std::vector<std::shared_ptr<Point>>{x, y, yh, xh})
		, Surface(std::vector<std::shared_ptr<Point>>{y, z, zh, yh})
		, Surface(std::vector<std::shared_ptr<Point>>{z, w, wh, zh})
		, Surface(std::vector<std::shared_ptr<Point>>{w, x, xh, wh})});*/
	std::vector<Figure> figures{ figure };
	std::shared_ptr<Point> firstAxisPoint = nullptr;
	std::shared_ptr<Point> secondAxisPoint = nullptr;
	window.display();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//points.push_back(std::shared_ptr<Point>(new Point(event.mouseButton.x, event.mouseButton.y, 100)));
					observator.move(0, 0, 10);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					if (firstAxisPoint == nullptr)
					{
						firstAxisPoint = std::shared_ptr<Point>(new Point(observator, event.mouseButton.x, event.mouseButton.y, 0));
						continue;
					}
					secondAxisPoint = std::shared_ptr<Point>(new Point(observator, event.mouseButton.x, event.mouseButton.y, 50));
					RotationAxis axis(firstAxisPoint, secondAxisPoint);
					firstAxisPoint = nullptr;
					secondAxisPoint = nullptr;
					figure.setRotation(axis);
				}
			}
			else if (event.type == event.KeyPressed)
			{
				sf::View currentView = window.getView();
				sf::Vector2f center = currentView.getCenter();
				if (event.key.code == sf::Keyboard::A)
				{
					/*center.x -= 10;
					currentView.setCenter(center);
					window.setView(currentView);*/
					observator.move(-observator.getDirectionVector().z/20, 0, -observator.getDirectionVector().x/20);
				}
				else if (event.key.code == sf::Keyboard::D)
				{
					/*center.x += 10;
					currentView.setCenter(center);
					window.setView(currentView);*/
					observator.move(observator.getDirectionVector().z / 20, 0, observator.getDirectionVector().x / 20);
				}
				else if (event.key.code == sf::Keyboard::W)
				{
					observator.move(observator.getDirectionVector().x/20, 0, observator.getDirectionVector().z/20);
				}
				else if (event.key.code == sf::Keyboard::S)
				{
					observator.move(-observator.getDirectionVector().x / 20, 0, -observator.getDirectionVector().z / 20);
				}
				else if (event.key.code == sf::Keyboard::Space)
				{
					observator.move(0, 0, -10);
				}
				else if (event.key.code == sf::Keyboard::Enter)
				{
					observator.move(0, 0, 10);
				}
				else if (event.key.code == sf::Keyboard::Left)
				{
					observator.rotateAround(0.01);
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					observator.rotateAround(-0.01);
				}
				else if (event.key.code == sf::Keyboard::Up)
				{
					observator.upLook(0.01);
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					observator.upLook(-0.01);
				}
			}
			else if (event.type == sf::Event::Closed)
				window.close();
		}
		for (auto& figure : figures)
		figure.move();
		draw(figures, window);
		Sleep(50);
		//Sleep(200);
		}
	return 0;
}

