#pragma once

#include "game_object.h"
#include "assets.h"
#include <stack>

class Player : public Game_Object 
{
public:
	Player();
	Player(std::string id, Vector_2D translation);
	~Player();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, Game_Manager* game_manager) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

	void set_speed(float speed);
	float speed();

	void push_state(State state, Assets* assets);
	void pop_state(Assets* assets);

	Game_Object::State current_state();

private:

	Uint32 _total_time_milliseconds;

	void handle_enter_state(State state, Assets* assets);
	void handle_exit_state(State state, Assets* assets);

	void slide();

	float _speed;

	const float _turning_angle = 3.5;

	std::stack<State> _state;
};