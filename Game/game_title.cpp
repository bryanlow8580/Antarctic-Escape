#include "game_title.h"

Game_Title::Game_Title(std::string id, Vector_2D translation)
	: Game_Object(id, "Texture.Game.Title")
{
	_translation = translation;

	_width = 500;
	_height = 350;
}

void Game_Title::simulate_AI(Uint32, Assets*, Input*, Scene*, Game_Manager*)
{
}