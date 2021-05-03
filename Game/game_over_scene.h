#pragma once

#include "scene.h"

class Game_Over_Scene : public Scene
{
public:
	Game_Over_Scene();
	~Game_Over_Scene();

	virtual void reset() override;

	virtual void update(SDL_Window* window) override;
};