#include "game_over_scene.h"
#include "game_over.h"

#include "sound.h"

Game_Over_Scene::Game_Over_Scene()
	: Scene("Game_Over")
{
	_game_objects.clear();

	Mix_HaltChannel(1);
	add_game_object(new Game_Over("Game.Over", Vector_2D(200, 100)));
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