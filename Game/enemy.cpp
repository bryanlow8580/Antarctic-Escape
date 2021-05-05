#pragma once

#include "enemy.h"
#include "animated_texture.h"

#include <time.h>

Enemy::Enemy(std::string id, Vector_2D translation)
	: Game_Object(id, "Texture.Enemy.Walking")
{
	_width = 130;
	_height = 130;

	_speed = 0.25f;
	_translation = translation;

	moved();
	turned();

	srand((Uint32)time(NULL) + rand() % 10000);
	_angle = rand() % 360;
	
	_blocked_by_wall = true;
}

Enemy::~Enemy()
{

}

void Enemy::moved()
{
	srand((Uint32)time(NULL) + rand() % 10000);
	_milliseconds_until_move = (rand() % 5 + 5) * 850;

	_milliseconds_of_movement = (rand() % 5 + 5) * 100;
}

void Enemy::turned()
{
	srand((Uint32)time(NULL) + rand() % 10000);
	_milliseconds_until_turn = (rand() % 5 + 5) * 700;

	_milliseconds_of_turn = (rand() % 10 + 5) * 100;

	_turn_direction = rand() % 2;
}

void Enemy::simulate_AI(Uint32 milliseconds_to_simulate, Assets*, Input*, Scene* scene, Game_Manager* game_manager)
{
	Game_Object* player = scene->get_game_object("Player");

	// Get location of center for enemy and player
	Vector_2D enemy_center = _translation + Vector_2D(_width / 2.0f, _height / 2.0f);
	Vector_2D player_center = player->translation() + Vector_2D(player->width() / 2.0f, player->height() / 2.0f);

	// Find distance to player 
	float distance_to_player = (enemy_center - player_center).magnitude();

	// If in range
	if (distance_to_player < 50.0f)
	{
		player->set_hp(0);
		game_manager->player_lose_life();
		scene->reset();
	}

	_velocity = Vector_2D(0, 0);

	if (_milliseconds_until_move <= 0)
	{
		if (_milliseconds_of_movement > 0)
		{
			const float PI = 3.14159265f;
			double radians = _angle * PI / 180;
			_velocity = Vector_2D(_velocity.x_from_angle(_speed, radians), _velocity.y_from_angle(_speed, radians));

			_milliseconds_of_movement -= milliseconds_to_simulate;
		}
		else
		{
			moved();
		}
	}

	if (_milliseconds_until_turn <= 0)
	{
		if (_milliseconds_of_turn > 0)
		{
			if (_turn_direction == 0)
			{
				// turn left
				_angle += _turn_speed;
			}
			else
			{
				// turn right
				_angle -= _turn_speed;
			}

			_milliseconds_of_turn -= milliseconds_to_simulate;
		}
		else
		{
			turned();
		}
	}

	_total_time_milliseconds += milliseconds_to_simulate;
	_milliseconds_until_move -= milliseconds_to_simulate;
	_milliseconds_until_turn -= milliseconds_to_simulate;
}

void Enemy::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{

	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->set_frame(_total_time_milliseconds);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);

}