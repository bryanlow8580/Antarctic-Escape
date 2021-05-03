#pragma once

#include "game_object.h"

class Walking_Dino : public Game_Object 
{
public: 
	Walking_Dino(std::string id, float x, float y);
	Walking_Dino(std::string id);
	~Walking_Dino();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, Game_Manager* game_manager) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

private:
	Uint32 _total_time_milliseconds;
	bool _has_spawned_another = false;
};