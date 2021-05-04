#pragma once

#include "vector_2D.h"

class Collider
{
public:
	Collider();
	Collider(float width, float height, Vector_2D translation);

	float height();
	float width();
	float weight();

	void set_height(float height);
	void set_width(float width);
	void set_weight(float weight);

	Vector_2D translation();
	void set_translation(Vector_2D translation);

	Vector_2D intersection_depth(Collider other);

protected:

	float _weight;

	float _height;
	float _width;
	Vector_2D _translation;
};