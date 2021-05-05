#include "game_victory_scene.h"
#include "game_victory.h"

#include "sound.h"

Game_Victory_Scene::Game_Victory_Scene()
	: Scene("Game_Victory")
{
	_game_objects.clear();

	add_game_object(new Game_Victory("Game.Victory", Vector_2D(200, 100)));
}

Game_Victory_Scene::~Game_Victory_Scene()
{

}

void Game_Victory_Scene::reset()
{
}

void Game_Victory_Scene::update(SDL_Window*)
{

}