#include "game_scene.h"
#include "ice.h"
#include "dino.h"
#include "walking_dino.h"
#include "running_dog.h"
#include "player.h"
#include "portal_entry.h"
#include "portal_exit.h"
#include "sound.h"
#include "assets.h"


Game_Scene::Game_Scene()
	: Scene("Game") 
{
	add_game_object(new Ice("Ice", 50, 300, 500, 200));
	add_game_object(new Ice("Ice2", 550, 500, 200, 500));
	add_game_object(new Dino("Dino"));
	add_game_object(new Walking_Dino("Dino.Walking"));
	//add_game_object(new Running_Dog("Dog.Running"));
	add_game_object(new Player("Player"));
	//add_game_object(new Portal_Entry("Portal.Entry"));
	//add_game_object(new Portal_Exit("Portal.Exit"));
}

Game_Scene::~Game_Scene() 
{

}

void Game_Scene::update(SDL_Window* window) 
{
	Game_Object* player = get_game_object("Player");

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	_camera_translation = Vector_2D(-w / 2.f + player->width() / 2.f, -h / 2.f + player->height() / 2.f) + player->translation();
}