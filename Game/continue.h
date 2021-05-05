#pragma once

#include "game_object.h"

class Continue : public Game_Object
{
public:
	Continue(std::string id, Vector_2D translation);

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, Game_Manager* game_manager);

};
