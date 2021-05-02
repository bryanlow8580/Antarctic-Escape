#include "circle_2D.h"

Circle_2D::Circle_2D(float radius, Vector_2D translation) 
	: Collider(radius, radius, translation) 
{
	_radius = radius;
	_width = radius;
	_height = radius;
}

float Circle_2D::radius() 
{
	return _radius;
}

void Circle_2D::set_radius(float radius) 
{
	_radius = radius;
	set_height(_radius);
	set_width(_radius);
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

// Circle to rectangle interaction
Vector_2D Circle_2D::intersection_depth(Collider other)
{
	if (_radius == 0.0f || other.height() == 0.0f || other.width() == 0.0f)
	{
		return Vector_2D(0, 0);
	}

	const float x_distance_to_other_collider = other.translation().x() - _translation.x();
	const float y_distance_to_other_collider = other.translation().y() - _translation.y();

	const float collider_height_combined = _radius + other.height();
	const float collider_width_combined = _radius + other.width();


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