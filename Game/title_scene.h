#pragma once

#include "scene.h"

class Title_Scene : public Scene
{
public:
	Title_Scene();
	~Title_Scene();

	virtual void reset() override;

	virtual void update(SDL_Window* window) override;
};
