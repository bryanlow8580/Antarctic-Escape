#include "portal_entry.h"

Portal_Entry::Portal_Entry(std::string id)
	: Game_Object(id, "Texture.Portal.Entry") 
{
	_width  = 200;
	_height = 200;

	_translation = Vector_2D(50, 350);
}

Portal_Entry::~Portal_Entry() 
{
}

// Disables int to float conversion warning
#pragma warning ( push )
#pragma warning ( disable : 4244 )

void Portal_Entry::simulate_AI(Uint32 milliseconds_to_simulate, Assets*, Input*, Scene* scene, Game_Manager*)
{

	// Get player object
	Game_Object* player = scene->get_game_object("Player");

	// Get location of center for portal and player
	Vector_2D portal_center = _translation + Vector_2D(_width / 2, _height / 2);
	Vector_2D player_center = player->translation() + Vector_2D(player->width() / 2, player->height() / 2);

	// Find distance to player 
	float distance_to_player = (portal_center - player_center).magnitude();

	// If in range
	if (distance_to_player < 50.0f) 
	{

		// Get exit portal location
		Game_Object* portal_exit = scene->get_game_object("Portal.Exit");
		Vector_2D exit_location = portal_exit->translation() + Vector_2D(100.f, 0.f);

		// Send player to location
		player->set_translation(exit_location);
	}

	_total_time_milliseconds += milliseconds_to_simulate;
}

#pragma warning ( pop )

void Portal_Entry::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) 
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->set_frame(_total_time_milliseconds);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}
