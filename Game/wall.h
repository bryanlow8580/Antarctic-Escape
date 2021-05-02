#pragma once

#include "game_object.h"

class Wall : public Game_Object
{
public: 
	Wall(std::string id, Vector_2D translation, int width, int height);
	~Wall();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;

private: 

};