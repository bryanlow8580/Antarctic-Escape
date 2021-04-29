#include "portal_exit.h"

Portal_Exit::Portal_Exit(std::string id) 
	: Game_Object(id, "Texture.Portal.Exit") 
{

	_width  = 200;
	_height = 200;

	_translation = Vector_2D(350, 350);
}

Portal_Exit::~Portal_Exit() 
{
}

void Portal_Exit::simulate_AI(Uint32 milliseconds_to_simulate, Assets*, Input*, Scene*) 
{
	_total_time_milliseconds += milliseconds_to_simulate;
}

void Portal_Exit::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) 
{

	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->set_frame(_total_time_milliseconds);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);

}
