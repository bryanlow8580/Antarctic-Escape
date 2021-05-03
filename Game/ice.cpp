#include "ice.h"
#include "player.h"
#include <iostream>

bool Ice::player_on_ice = false;

Ice::Ice(std::string id, Vector_2D translation, int width, int height)
	: Game_Object(id, "Texture.Ice")
{
	_width = width;
	_height = height;

	_translation = translation;
}

Ice::~Ice()
{

}

void Ice::simulate_AI(Uint32, Assets* assets, Input*, Scene* scene, Game_Manager*)
{
	Player* player = (Player*)scene->get_game_object("Player");
	float player_x = player->translation().x();
	float player_y = player->translation().y();

	int offset_x = player->width()/2 - 5;
	int offset_y = player->height()/2 - 5;
	
	if (player_x >= _translation.x() - offset_x && player_x <= _translation.x() + _width - offset_x
		&& player_y >= _translation.y() - offset_y && player_y <= _translation.y() + _height - offset_y)
	{
		// If player is within boundaries of ice, and not already in sliding or dying state, push sliding state
		if (player->current_state() != State::Sliding && player->current_state() != State::Dying)
		{
			std::cout << "START SLIDE\n";
			player_on_ice = true;
			player->push_state(State::Sliding, assets);
		}
	}
	else if (player_on_ice)
	{
		// doesnt work if theres more than one ice object, help
		// If player is outside boundaries
		player_on_ice = false;
		player->pop_state(assets);
	}
}

