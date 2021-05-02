#include "wall.h"

Wall::Wall(std::string id, Vector_2D translation, int width, int height)
	: Game_Object(id, "Texture.Collider.Rectangle")
{

	_width		 = width;
	_height		 = height;
	_translation = translation;

	_collider.set_width((float)width);
	_collider.set_height((float)height);
	_collider.set_translation(translation);

}

Wall::~Wall()
{

}

void Wall::simulate_AI(Uint32 , Assets* , Input* , Scene* )
{

}