#include "Point.h"
#include <math.h>

Point::Point(Observator& o, const float& x,const float& y,const float& z)
: Position(x,y,z),
  observator(o)
{
	cast();
}
Point::Point(const Point& p)
: Position(x, y, z),
observator(p.observator)
{
	//setRotation(p.rotationCenter);
	cast();
}
Point::~Point()
{
}
Position Point::getPosition() const
{
	return Position(x,y,z);
}
void Point::setPosition(const Position& p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}
float Point::getXSpeed() const
{
	return xSpeed;
}
float Point::getYSpeed() const
{
	return ySpeed;
}
float Point::getZSpeed() const
{
	return zSpeed;
}
float Point::getXAccelaration() const
{
	return xAccelaration;
}
float Point::getYAccelaration() const
{
	return yAccelaration;
}
float Point::getZAccelaration() const
{
	return zAccelaration;
}
void Point::setRotation(const Position& centerPoint, const Position& axisVector)
{
	rotationCenter = centerPoint; 
	radius = distanceBetweenPoints(*this, rotationCenter);
	totalSpeed = 2 * 333 / 106 * radius / timeForSpin;
	totalAccelaration = (totalSpeed*totalSpeed / radius);
	setSpeedtoRotate(axisVector);
	setAccelaration();
}
void Point::setSpeed()
{
	xSpeed += xAccelaration;
	ySpeed += yAccelaration;
	zSpeed += zAccelaration;
	if (sqrt(xSpeed*xSpeed + ySpeed*ySpeed + zSpeed*zSpeed) == 0)
		return;
	float deltaSpeed = totalSpeed / sqrt(xSpeed*xSpeed + ySpeed*ySpeed + zSpeed*zSpeed);
	xSpeed *= deltaSpeed;
	ySpeed *= deltaSpeed;
	zSpeed *= deltaSpeed;
}
void Point::setAccelaration()
{
	float dx = rotationCenter.x - x;
	float dy = rotationCenter.y - y;
	float dz = rotationCenter.z - z;
	float factor = sqrt(totalAccelaration*totalAccelaration / (dx*dx + dy*dy + dz*dz));
	xAccelaration = dx*factor;
	yAccelaration = dy*factor;
	zAccelaration = dz*factor;
}
void Point::move()
{
	x += xSpeed;
	y += ySpeed;
	z += zSpeed;
	cast();
	setSpeed();
	setAccelaration();
}

float Point::getRadius() const
{
	return radius;
}
Position Point::getRotationCenter() const
{
	return rotationCenter;
}
void Point::cast()
{
	Position& vec = observator.getDirectionVector();
	//Position middlePoint{ observator.x + vec.x, observator.y + vec.y, observator.z + vec.z };
	//float a1 = -1 / (vec.x / vec.z);
	//float b1 = middlePoint.z / a1 / middlePoint.x; // y = ax + b // b = y / ax
	//float a2 = (observator.z - z) / (observator.x - x);//y1 = a2x1 + b2 ; -y2 = -a2x2 - b2 ; y1-y2 = a2(x1-y1) ; a2 = y1-y2 / x1-x2
	//float b2 = z - a2*x;//b2 = z1 - a2x1;
	//xCast = (b1 - b2) / (a2 - a1);//z = a1x + b1; z = a2x + b2 ;  0 = a2x - a1x + b2 - b1 ; 0 = x(a2 - a1) + b2-b1 ; (b1 - b2) / (a2 - a1);
	//a1 = -1 / (vec.y / vec.z);
	//b1 = middlePoint.z / a1 / middlePoint.x; // y = ax + b // b = y / ax
	//a2 = (observator.z - z) / (observator.y - y);//y1 = a2x1 + b2 ; -y2 = -a2x2 - b2 ; y1-y2 = a2(x1-y1) ; a2 = y1-y2 / x1-x2
	//b2 = z - a2*y;//b2 = z1 - a2x1;
	//yCast = (b1 - b2) / (a2 - a1);
	float px = x - observator.x;
	float pz = z - observator.z;
	float tana = (vec.x/vec.z - px/pz) / (1 + vec.x*px/vec.z/pz);
	float alpha = atan(tana);
	float distance = 200 * alpha;
	xCast = 600 - 5*distance;
	float py = y - observator.y;
	tana = (vec.y / vec.z - py / pz) / (1 + vec.y*py / vec.z / pz);
	alpha = atan(tana); 
	distance = 200 * alpha;
	yCast = 300 + 5*distance;
}
template<class T1, class T2>
float Point::distanceBetweenPoints(const T1& p1, const T2& p2)
{
	float xpow = pow(p1.x - p2.x, 2);
	float ypow = pow(p1.y - p2.y, 2);
	float zpow = pow(p1.z - p2.z, 2);
	return sqrt(xpow + ypow + zpow);
}
void Point::setSpeedtoRotate(const Position& axisV)
{
	float rx = x - rotationCenter.x;
	float ry = y - rotationCenter.y;
	float rz = z - rotationCenter.z; 
	float VxSpeed = ry*axisV.z - axisV.y*rz;
	float VySpeed = -rx*axisV.z + axisV.x*rz;
	float VzSpeed = rx*axisV.y - axisV.x*ry;
	float fraction = sqrt(totalSpeed*totalSpeed / (VxSpeed*VxSpeed + VySpeed*VySpeed + VzSpeed*VzSpeed));
	xSpeed = VxSpeed * fraction;
	ySpeed = VySpeed * fraction;
	zSpeed = VzSpeed * fraction;
}