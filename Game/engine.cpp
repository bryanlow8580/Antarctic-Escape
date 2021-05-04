#include "engine.h"
#include "texture.h"
#include "animated_texture.h"
#include "game_object.h"

// Must always be defined before including SDL.h
#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <sdl_image.h>
#include <iostream>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <algorithm>

Engine::Engine(std::string window_name, Configuration* config) 
{
	const int init_result		  = SDL_Init(SDL_INIT_EVERYTHING);
	const int init_result_success = 0;
	
	if(init_result != init_result_success) 
	{
		std::cout << "Failed to initialize SDL" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	// Window properties

	const char* game_title = window_name.c_str();
	const int x			   = 100;
	const int y			   = 100;

	_window = SDL_CreateWindow(game_title, x, y, config->window_width, config->window_height, SDL_WINDOW_RESIZABLE);

	if (_window == nullptr) 
	{
		std::cout << "Failed to create SDL window" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	_renderer = SDL_CreateRenderer(_window, -1, 0);

	if (_renderer == nullptr) 
	{
		std::cout << "Failed to create Renderer" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	// SDL PNG Image

	const int image_init_result  = IMG_Init(IMG_INIT_PNG);
	const int image_init_success = IMG_INIT_PNG;

	if (image_init_result != image_init_success) 
	{
		std::cout << "Failed to initialize SDL Image" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const int ttf_init_result  = TTF_Init();
	const int ttf_init_success = 0;

	if (ttf_init_result != ttf_init_success) 
	{
		std::cout << "Failed to initialize SDL TTF" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	// Initialize SDL Mixer

	const int mixer_init_result  = Mix_Init(MIX_INIT_MOD);
	const int mixer_init_failure = 0;

	if (mixer_init_result == mixer_init_failure) 
	{
		std::cout << "Failed to initialize SDL Mixer" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		std::cout << "Mixer Error: " << Mix_GetError() << std::endl;
		exit(1);
	}

	// Open Audio

	const int mixer_open_audio_result  = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	const int mixer_open_audio_success = 0;
	if (mixer_open_audio_result != mixer_open_audio_success) 
	{
		std::cout << "Failed to open audio" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	Mix_AllocateChannels(3);
}

Engine::~Engine() 
{

}

void Engine::simulate(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Input* input, Configuration* config, Game_Manager* game_manager) 
{
	simulate_AI(milliseconds_to_simulate, assets, scene, input, game_manager);
	simulate_physics(milliseconds_to_simulate, assets, scene);
	render(milliseconds_to_simulate, assets, scene, config);
	
}

void Engine::simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Input* input, Game_Manager* game_manager) 
{
	std::vector<Game_Object*> game_objects = scene->get_game_objects();

	for (Game_Object* game_object : game_objects) 
	{
		game_object->simulate_AI(milliseconds_to_simulate, assets, input, scene, game_manager);
	}
}

void Engine::simulate_physics(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene) 
{
	std::vector<Game_Object*> game_objects = scene->get_game_objects();

	for (Game_Object* game_object : game_objects) 
	{
		game_object->simulate_physics(milliseconds_to_simulate, assets, scene);
	}
}

void Engine::render(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Configuration* config) 
{
	// Clear renderer
	const int render_clear_success = 0;
	const int render_clear_result = SDL_RenderClear(_renderer);

	// Check if renderer was cleared
	if (render_clear_result != render_clear_success) 
	{
		std::cout << "Failed to clear Renderer" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	// Background colour
	const Uint8 red   = 200;
	const Uint8 green = 200;
	const Uint8 blue  = 200;
	const Uint8 alpha = 255;

	std::vector<Game_Object*> sorted_game_objects = scene->get_game_objects();

	const struct
	{
		bool operator()(Game_Object* a, Game_Object* b)
		{
			if (a->id().find("Ice") != -1 && b->id().find("Ice") == -1)
			{
				return true;
			}
			else if (a->id().find("Ice") == -1 && b->id().find("Ice") != -1)
			{
				return false;
			}
			return a->translation().y() < b->translation().y();
		}
	} sort_by_y_order;
	std::sort(sorted_game_objects.begin(), sorted_game_objects.end(), sort_by_y_order);

	for (Game_Object* game_object : sorted_game_objects) 
	{
		game_object->render(milliseconds_to_simulate, assets, _renderer, config, scene);
	}

	// Set render background colour
	SDL_SetRenderDrawColor(_renderer, red, green, blue, alpha);

	SDL_RenderPresent(_renderer);
}


SDL_Renderer* Engine::renderer() 
{
	return _renderer;
}

SDL_Window* Engine::window() 
{
	return _window;
}
