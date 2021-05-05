#include "title_scene.h"
#include "game_title.h"
#include "continue.h"

Title_Scene::Title_Scene()
	: Scene("Game.Title")
{
	_game_objects.clear();

	add_game_object(new Game_Title("Game.Title", Vector_2D(200, 50)));
	add_game_object(new Continue("Game.Continue", Vector_2D(450, 400)));
}

Title_Scene::~Title_Scene()
{

}

void Title_Scene::reset()
{
}

void Title_Scene::update(SDL_Window*)
{

}