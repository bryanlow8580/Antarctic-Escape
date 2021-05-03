#pragma once

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include "assets.h"
#include "scene.h"
#include "input.h"
#include "configuration.h"
#include "game_manager.h"

class Engine 
{
public: 
	Engine(std::string window_name, Configuration* config);
	~Engine();

	void simulate(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Input* input, Configuration* config, Game_Manager* game_manager);

	SDL_Window* window();
	SDL_Renderer* renderer();

private:
	void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Input* input, Game_Manager* game_manager);
	void simulate_physics(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene);
	void render(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Configuration* config);

	SDL_Window*	  _window;
	SDL_Renderer* _renderer;
};