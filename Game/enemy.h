#pragma once

#include "game_object.h"

class Enemy : public Game_Object
{
public:
	Enemy(std::string id, Vector_2D translation);
	~Enemy();


	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, Game_Manager* game_manager) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

private:
	void moved();
	void turned();

	Uint32 _total_time_milliseconds;

	int _milliseconds_until_move;
	int _milliseconds_of_movement;

	int _milliseconds_until_turn;
	int _milliseconds_of_turn;

	// 0 for left, 1 for right
	bool _turn_direction;

	const float _turn_speed = 3;
	float _speed;

};