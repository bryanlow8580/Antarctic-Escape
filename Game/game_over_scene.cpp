#include "game_over_scene.h"
#include "flag.h"

#include "sound.h"
#include "assets.h"


Game_Over_Scene::Game_Over_Scene()
	: Scene("Game_Over")
{
	_game_objects.clear();

	// TODO - add game over screen stuff
	add_game_object(new Flag("Flag", Vector_2D(50, 50)));
}

Game_Over_Scene::~Game_Over_Scene()
{

}

void Game_Over_Scene::reset()
{
}

void Game_Over_Scene::update(SDL_Window*)
{

}