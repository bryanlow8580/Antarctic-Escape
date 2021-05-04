#pragma once

#include "collider.h"

class Circle_2D : public Collider
{
public:
	Circle_2D(float radius, Vector_2D translation);

	float radius();
	void set_radius(float radius);

	float intersection_depth(Circle_2D other);
	Vector_2D intersection_depth(Collider other);

private:
	float _radius;
	Collider _collider;
};