#pragma once

#include "running_dog.h"
#include "animated_texture.h"

Running_Dog::Running_Dog(std::string id) 
	: Game_Object(id, "Texture.Dog.Running") 
{
	
	_translation = Vector_2D(50, 150);
}

Running_Dog::~Running_Dog() 
{

}


// Disables int to float conversion warning
#pragma warning ( push )
#pragma warning ( disable : 4244 )

void Running_Dog::simulate_AI(Uint32 milliseconds_to_simulate, Assets*, Input*, Scene* scene, Game_Manager* game_manager)
{

	Game_Object* player = scene->get_game_object("Player");

	// Get location of center for portal and player
	Vector_2D dog_center = _translation + Vector_2D(_width / 2, _height / 2);
	Vector_2D player_center = player->translation() + Vector_2D(player->width() / 2, player->height() / 2);

	// Find distance to player 
	float distance_to_player = (dog_center - player_center).magnitude();

	// If in range
	if (distance_to_player < 50.0f) 
	{
		player->set_hp(0);
		game_manager->player_lose_life();
		scene->reset();
	}

	_total_time_milliseconds += milliseconds_to_simulate;

}


#pragma warning ( pop )

void Running_Dog::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) 
{

	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->set_frame(_total_time_milliseconds);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);

}