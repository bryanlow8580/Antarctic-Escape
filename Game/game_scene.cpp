#include "game_scene.h"
#include "ice.h"
#include "dino.h"
#include "walking_dino.h"
#include "running_dog.h"
#include "player.h"
#include "portal_entry.h"
#include "portal_exit.h"
#include "wall.h"

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
	
	add_game_object(new Ice("Ice", Vector_2D(150, 250), 600, 400));
	//add_game_object(new Ice("Ice2", Vector_2D(750, 250), 300, 600));
	add_game_object(new Player("Player"));
	//add_game_object(new Dino("Dino"));
	//add_game_object(new Walking_Dino("Dino.Walking"));
	add_game_object(new Running_Dog("Dog.Running"));
	//add_game_object(new Portal_Entry("Portal.Entry"));
	//add_game_object(new Portal_Exit("Portal.Exit"));
	add_game_object(new Wall("Wall", Vector_2D(150, 650), 600, 50));
}

void Game_Scene::update(SDL_Window* window) 
{
	Game_Object* player = get_game_object("Player");

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	_camera_translation = Vector_2D(-w / 2.f + player->width() / 2.f, -h / 2.f + player->height() / 2.f) + player->translation();
}