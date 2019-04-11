#pragma once
#include "Position.h"
#include "Observator.h"
#include <memory>
class Point : 
	public Position
{
	Observator& observator;
	float xSpeed{};
	float ySpeed{};
	float zSpeed{};
	float xAccelaration{};
	float yAccelaration{};
	float zAccelaration{};
	const float timeForSpin = 100;
	float totalSpeed;
	float totalAccelaration{};
	//radius for a circle, that object will rotate on
	float radius{};
	//center of that circle
	Position rotationCenter;
	void setSpeed();
	void setAccelaration();
	void cast();
	void setSpeedtoRotate(const Position&);
public:
	Point(Observator&, const float& x = 0, const float& y = 0, const float& z = 0);
	Point(const Point&);
	Point& operator = (const Point& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		//setRotation(*rotationAxis);
		cast();
		return *this;
	}
	bool operator == (const Point& p)
	{
		return (x == p.x && y == p.y && z == p.z);
	}
	virtual ~Point();
	Position getPosition() const;
	void setPosition(const Position&);
	float getXSpeed() const;
	float getYSpeed() const;
	float getZSpeed() const;
	float getXAccelaration() const;
	float getYAccelaration() const;
	float getZAccelaration() const;
	void setRotation(const Position&, const Position&);
	void move();
	float getRadius() const;
	Position getRotationCenter() const;
	float xCast;
	float yCast;
	template<class T1,class T2>
	static float distanceBetweenPoints(const T1&, const T2&);
};

