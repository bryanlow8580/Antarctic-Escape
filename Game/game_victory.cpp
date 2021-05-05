#include "game_victory.h"

Game_Victory::Game_Victory(std::string id, Vector_2D translation)
	: Game_Object(id, "Texture.Game.Victory")
{
	_translation = translation;

	_width = 500;
	_height = 500;
}

void Game_Victory::simulate_AI(Uint32, Assets*, Input*, Scene*, Game_Manager*)
{

};