#pragma once

#include "game_object.h"

class Life : public Game_Object
{
public:
	Life(std::string id, Vector_2D translation);
	~Life();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, Game_Manager* game_manager) override;
	void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene);
};