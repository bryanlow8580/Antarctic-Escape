#include "circle_2D.h"

Circle_2D::Circle_2D(float radius, Vector_2D translation) 
	: _translation(translation.x(), translation.y())
{
	_radius = radius;
}

float Circle_2D::radius() 
{
	return _radius;
}

void Circle_2D::set_radius(float radius) 
{
	_radius = radius;
}

// Circle to circle intersection
float Circle_2D::intersection_depth(Circle_2D other) 
{
	if (_radius == 0.0f || other._radius == 0.0f) 
	{
		return 0.0;
	}

	const float distance_to_other_collider = (other.translation() - _translation).magnitude();
	const float collider_radius_combined = _radius + other.radius();

	if (distance_to_other_collider < collider_radius_combined) 
	{

		return collider_radius_combined - distance_to_other_collider;
	}
	else 
	{
		return 0;
	}
}

Vector_2D Circle_2D::translation()
{
	return _translation;
}

void Circle_2D::set_translation(Vector_2D translation)
{
	_translation = translation;
}