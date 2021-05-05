#pragma once

#include "scene.h"

class Game_Victory_Scene : public Scene
{
public:
	Game_Victory_Scene();
	~Game_Victory_Scene();

	virtual void reset() override;

	virtual void update(SDL_Window* window) override;

};