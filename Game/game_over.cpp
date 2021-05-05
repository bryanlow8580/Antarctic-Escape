#include "game_over.h"

Game_Over::Game_Over(std::string id, Vector_2D translation)
	: Game_Object(id, "Texture.Game.Over")
{
	_translation = translation;

	_width = 500;
	_height = 500;
}

void Game_Over::simulate_AI(Uint32, Assets*, Input*, Scene*, Game_Manager*)
{

};