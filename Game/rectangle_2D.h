#pragma once

#include "vector_2D.h"
#include "collider.h"

class Rectangle_2D : public Collider
{
public:
	Rectangle_2D(float height, float width, Vector_2D translation);
	~Rectangle_2D();
};