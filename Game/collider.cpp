#include "collider.h"

Collider::Collider(float height, float width, Vector_2D translation)
	: _translation(translation.x(), translation.y())
{
	_height = height;
	_width = width;
	_translation = translation;
}

float Collider::height() 
{
	return _height;
}

float Collider::width()
{
	return _width;
}

void Collider::set_height(float height) 
{
	_height = height;
}

void Collider::set_width(float width)
{
	_width = width;
}

Vector_2D Collider::translation()
{
	return _translation;
}

void Collider::set_translation(Vector_2D translation)
{
	_translation = translation;
}

Vector_2D Collider::intersection_depth(Collider other)
{
	if (_height == 0.0f ||_width == 0.0f || other._height == 0.0f || other._width == 0.0f)
	{
		return Vector_2D(0, 0);
	}

	const float x_distance_to_other_collider = other.translation().x() - _translation.x();
	const float y_distance_to_other_collider = other.translation().y() - _translation.y();

	const float collider_height_combined = _height + other.height();
	const float collider_width_combined = _width + other.width();

	if (x_distance_to_other_collider < collider_width_combined)
	{
		if (y_distance_to_other_collider < collider_height_combined)
		{
			return Vector_2D(collider_width_combined - x_distance_to_other_collider, collider_height_combined - y_distance_to_other_collider);
		}
		else
		{
			return Vector_2D(0, 0);
		}
	}
	else
	{
		return Vector_2D(0, 0);
	}
}