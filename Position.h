#pragma once
class Position
{
public:
	Position(const float& x = 0,const float& y = 0,const float& z = 0);
	Position(const Position&);
	Position& operator = (const Position& p)
	{
		x = p.x;
		y = p.y;
		z = p.z;
		return*this;
	}
	~Position();
	float getX() const;
	float getY() const;
	float getZ() const;
	void setX(float);
	void setY(float);
	void setZ(float);
	float x;
	float y;
	float z;
};


