#include "game_scene.h"
#include "ice.h"
#include "player.h"
#include "enemy.h"
#include "wall.h"
#include "flag.h"

#include "sound.h"
#include "assets.h"


Game_Scene::Game_Scene()
	: Scene("Game") 
{
	reset();
}

Game_Scene::~Game_Scene() 
{

}

void Game_Scene::reset()
{
	_game_objects.clear();
	
	add_game_object(new Ice("Ice", Vector_2D(150, 200), 5000, 5000));
	add_game_object(new Player("Player", Vector_2D(50, 250)));

	add_game_object(new Enemy("Enemy1", Vector_2D(50, 400)));

	add_game_object(new Wall("Wall_Uppermost", Vector_2D(0, 200), 5000, 50));
	add_game_object(new Wall("Wall_Below_Spawn", Vector_2D(0, 650), 600, 50));
	add_game_object(new Wall("Wall_Left_Of_Spawn", Vector_2D(0, 200), 50, 500));
	add_game_object(new Wall("Wall_Straight_Ahead", Vector_2D(1000, 200), 50, 1000));
	add_game_object(new Wall("Wall_Straight_Down", Vector_2D(450, 1000), 600, 50));

	add_game_object(new Flag("Flag", Vector_2D(0, 2000)));
}

void Game_Scene::update(SDL_Window* window) 
{
	Game_Object* player = get_game_object("Player");

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	_camera_translation = Vector_2D(-w / 2.f + player->width() / 2.f, -h / 2.f + player->height() / 2.f) + player->translation();
}