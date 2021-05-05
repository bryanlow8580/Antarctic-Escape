#include "game_scene.h"
#include "ice.h"
#include "player.h"
#include "enemy.h"
#include "wall.h"
#include "flag.h"

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
	
	add_game_object(new Ice("Ice", Vector_2D(150, 200), 2150, 1850));
	add_game_object(new Player("Player", Vector_2D(50, 400)));

	
	// Part 1 - 8 enemies
	// x range = 350 - 2200
	// y range = 250 - 700
	add_game_object(new Enemy("Enemy_Part1_1", Vector_2D(350, 400)));
	add_game_object(new Enemy("Enemy_Part1_2", Vector_2D(500, 642)));
	add_game_object(new Enemy("Enemy_Part1_3", Vector_2D(700, 570)));
	add_game_object(new Enemy("Enemy_Part1_4", Vector_2D(1000, 345)));
	add_game_object(new Enemy("Enemy_Part1_5", Vector_2D(1300, 631)));
	add_game_object(new Enemy("Enemy_Part1_6", Vector_2D(1500, 604)));
	add_game_object(new Enemy("Enemy_Part1_7", Vector_2D(1800, 315)));
	add_game_object(new Enemy("Enemy_Part1_8", Vector_2D(1900, 455)));

	// Part 2 - 8 enemies
	// x range = 350 - 2200
	// y range = 800 - 1150
	add_game_object(new Enemy("Enemy_Part2_1", Vector_2D(356, 863)));
	add_game_object(new Enemy("Enemy_Part2_2", Vector_2D(752, 942)));
	add_game_object(new Enemy("Enemy_Part2_3", Vector_2D(1642, 1053)));
	add_game_object(new Enemy("Enemy_Part2_4", Vector_2D(1757, 950)));
	add_game_object(new Enemy("Enemy_Part2_5", Vector_2D(1357, 927)));
	add_game_object(new Enemy("Enemy_Part2_6", Vector_2D(2000, 1037)));
	add_game_object(new Enemy("Enemy_Part2_7", Vector_2D(456, 875)));
	add_game_object(new Enemy("Enemy_Part2_8", Vector_2D(731, 902)));

	// Part 3 - 10 enemies
	// x range = 350 - 2200
	// y range = 1250 - 1550
	add_game_object(new Enemy("Enemy_Part3_1", Vector_2D(356, 1357)));
	add_game_object(new Enemy("Enemy_Part3_2", Vector_2D(653, 1257)));
	add_game_object(new Enemy("Enemy_Part3_3", Vector_2D(758, 1473)));
	add_game_object(new Enemy("Enemy_Part3_4", Vector_2D(1532, 1500)));
	add_game_object(new Enemy("Enemy_Part3_5", Vector_2D(1841, 1531)));
	add_game_object(new Enemy("Enemy_Part3_6", Vector_2D(1292, 1436)));
	add_game_object(new Enemy("Enemy_Part3_7", Vector_2D(2013, 1402)));
	add_game_object(new Enemy("Enemy_Part3_8", Vector_2D(1632, 1487)));
	add_game_object(new Enemy("Enemy_Part3_9", Vector_2D(865, 1322)));
	add_game_object(new Enemy("Enemy_Part3_10", Vector_2D(2164, 1517)));

	// Part 4 - 10 enemies
	// x range = 350 - 2200
	// y range = 1650 - 1950
	add_game_object(new Enemy("Enemy_Part4_1", Vector_2D(746, 1733)));
	add_game_object(new Enemy("Enemy_Part4_2", Vector_2D(632, 1926)));
	add_game_object(new Enemy("Enemy_Part4_3", Vector_2D(1644, 1825)));
	add_game_object(new Enemy("Enemy_Part4_4", Vector_2D(1278, 1861)));
	add_game_object(new Enemy("Enemy_Part4_5", Vector_2D(2011, 1921)));
	add_game_object(new Enemy("Enemy_Part4_6", Vector_2D(1622, 1692)));
	add_game_object(new Enemy("Enemy_Part4_7", Vector_2D(360, 1931)));
	add_game_object(new Enemy("Enemy_Part4_8", Vector_2D(951, 1821)));
	add_game_object(new Enemy("Enemy_Part4_9", Vector_2D(1355, 1731)));
	add_game_object(new Enemy("Enemy_Part4_10", Vector_2D(1011, 1764)));

	add_game_object(new Wall("Wall_Uppermost", Vector_2D(0, 200), 2300, 50));
	add_game_object(new Wall("Wall_Below_Spawn", Vector_2D(0, 750), 2000, 50));
	add_game_object(new Wall("Wall_Left_Of_Spawn", Vector_2D(0, 200), 50, 600));
	add_game_object(new Wall("Wall_Rightmost", Vector_2D(2250, 200), 50, 1850));

	add_game_object(new Wall("Wall_Part2_Leftmost", Vector_2D(150, 750), 50, 900));
	add_game_object(new Wall("Wall_Part2_Bottom", Vector_2D(450, 1200), 1850, 50));
	add_game_object(new Wall("Wall_Part3_Bottom", Vector_2D(0, 1600), 2000, 50));
	add_game_object(new Wall("Wall_Bottommost", Vector_2D(0, 2000), 2300, 50));

	add_game_object(new Wall("Wall_Left_Of_Goal", Vector_2D(0, 1600), 50, 450));



	add_game_object(new Flag("Flag", Vector_2D(50, 1750)));
}

void Game_Scene::update(SDL_Window* window) 
{
	Game_Object* player = get_game_object("Player");

	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	_camera_translation = Vector_2D(-w / 2.f + player->width() / 2.f, -h / 2.f + player->height() / 2.f) + player->translation();
}