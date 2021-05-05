#pragma once

#include "game_object.h"

class Game_Over : public Game_Object
{
public:
	Game_Over(std::string id, Vector_2D translation);

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, Game_Manager* game_manager);

};
