#pragma once

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <string>

#include "assets.h"
#include "input.h"
#include "vector_2D.h"
#include "circle_2D.h"
#include "scene.h"
#include "configuration.h"
#include "game_manager.h"

class Game_Object 
{
public:
	Game_Object(std::string id, std::string texture_id);
	~Game_Object();

	enum class State
	{
		Idle,
		Walking,
		Sliding,
		Dying
	};

	std::string id();
	Vector_2D translation();
	void set_translation(Vector_2D translation);
	int width();
	int height();
	bool blocked_by_wall();

	void set_hp(int hp);

	Vector_2D velocity();

	// = 0 at the end of declaration informs compiler that the method is abstract (aka pure virtual)
	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, Game_Manager* game_manager) = 0;
	virtual void simulate_physics(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene);
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene);

	Circle_2D collider();


protected:
	std::string _id;
	std::string _texture_id;

	Circle_2D _collider;

	Vector_2D _translation; // Current pos 
	Vector_2D _velocity;	// Direction & speed

	double _angle;
	int _width;
	int _height;

	int _hp;

	bool _blocked_by_wall;

	SDL_RendererFlip _flip;
};