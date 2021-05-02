#pragma once

#include "game_object.h"

class Ice : public Game_Object 
{
public:
	Ice(std::string id, Vector_2D translation, int width, int height);
	~Ice();

	void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;

private:
	static bool player_on_ice;
};