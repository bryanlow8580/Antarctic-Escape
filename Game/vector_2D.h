#pragma once

class Vector_2D 
{
public:
	Vector_2D(float x, float y);

	float x();
	float y();

	void operator=(Vector_2D rhs);
	void operator+=(Vector_2D rhs);

	Vector_2D operator-(Vector_2D rhs);
	Vector_2D operator+(Vector_2D rhs);

	float magnitude();
	void normalize();
	void scale(float scalar);
	float angle();

	float x_from_angle(float magnitude, double angle);
	float y_from_angle(float magnitude, double angle);

private:
	float _x;
	float _y;
};