#include "life.h"

Life::Life(std::string id, Vector_2D translation)
	: Game_Object(id, "Texture.Life")
{
	_width = 30;
	_height = 30;
	_translation = translation;
}

Life::~Life()
{

}

void Life::simulate_AI(Uint32, Assets*, Input*, Scene*, Game_Manager*)
{

}

void Life::render(Uint32, Assets* assets, SDL_Renderer* renderer, Configuration*, Scene*)
{
	SDL_Rect destination;

	destination.x = (int)(_translation.x());
	destination.y = (int)(_translation.y());
	destination.w = _width;
	destination.h = _height;

	Texture* texture = (Texture*)assets->get_asset(_texture_id);
	texture->render(renderer, nullptr, &destination, SDL_FLIP_NONE, _angle);
}