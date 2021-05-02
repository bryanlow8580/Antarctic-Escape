#include "vector_2D.h"
#include <corecrt_math.h>

Vector_2D::Vector_2D(float x, float y) 
{
	_x = x;
	_y = y;
}

float Vector_2D::x() 
{
	return _x;
}

float Vector_2D::y() 
{
	return _y;
}

// Sets Vector to another Vectors value
void Vector_2D::operator=(Vector_2D rhs) 
{
	_x = rhs._x;
	_y = rhs._y;
}

// Adds Vector value to another Vector using +=
void Vector_2D::operator+=(Vector_2D rhs) 
{
	_x += rhs._x;
	_y += rhs._y;
}

// Subtracts Vector value from another Vector
Vector_2D Vector_2D::operator-(Vector_2D rhs) 
{
	return Vector_2D(_x - rhs._x, _y - rhs._y);
}

// Adds Vector value from another vector
Vector_2D Vector_2D::operator+(Vector_2D rhs) 
{
	return Vector_2D(_x + rhs._x, _y + rhs._y);
}

// Returns length of Vector
float Vector_2D::magnitude() 
{
	return sqrtf(_x * _x + _y * _y);
}

void Vector_2D::normalize() 
{
	float mag = magnitude();

	if (mag > 0.0f) 
	{
		_x /= mag;
		_y /= mag;
	}
}

void Vector_2D::scale(float scalar) 
{
	_x *= scalar;
	_y *= scalar;
}

float Vector_2D::angle() 
{
	return -atan2f(_y, _x);
}

// angle in radians
float Vector_2D::x_from_angle(float magnitude, double angle)
{
	return (float)(magnitude * cos(angle));
}

// angle in radians
float Vector_2D::y_from_angle(float magnitude, double angle)
{
	return (float)(magnitude * sin(angle));
}