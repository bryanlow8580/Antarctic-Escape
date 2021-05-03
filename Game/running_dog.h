#pragma once

#include "game_object.h"

class Running_Dog : public Game_Object 
{
public:
	Running_Dog(std::string id);
	~Running_Dog();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, Game_Manager* game_manager) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

private:
	Uint32 _total_time_milliseconds;
};