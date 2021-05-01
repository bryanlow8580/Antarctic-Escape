#include "ice.h"
#include "player.h"
#include <iostream>

bool Ice::player_on_ice = false;

Ice::Ice(std::string id, float x, float y, int width, int height)
	: Game_Object(id, "Texture.Ice")
{
	_width = width;
	_height = height;

	_translation = Vector_2D(x, y);
}

Ice::~Ice()
{

}

void Ice::simulate_AI(Uint32, Assets* assets, Input*, Scene* scene)
{
	Player* player = (Player*)scene->get_game_object("Player");
	float player_x = player->translation().x();
	float player_y = player->translation().y();
	
	if (!player_on_ice)
	{
		if (player_x >= _translation.x() - 70 && player_x <= _translation.x() + _width - 50)
		{
			if (player_y >= _translation.y() - 100 && player_y <= _translation.y() + _height - 100)
			{
				// If player is within boundaries of ice, and not already in sliding or dying state, push sliding state
				if (player->current_state() != State::Sliding && player->current_state() != State::Dying)
				{
					std::cout << "START SLIDE\n";
					player_on_ice = true;
					player->push_state(State::Sliding, assets);
				}
			}
		}
	} 
	else
	{
		if ((player_x < _translation.x() - 70 || player_x > _translation.x() + _width - 50) && (player_x < _translation.y() - 100 || player_x > _translation.y() + _height - 100))
		{
			// If player is outside boundaries
			player_on_ice = false;
			player->pop_state(assets);
		}
	}
}

