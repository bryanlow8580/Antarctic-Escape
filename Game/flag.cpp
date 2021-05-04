#include "flag.h"


Flag::Flag(std::string id, Vector_2D translation)
	: Game_Object(id, "Texture.Flag")
{
	_translation = translation;
	
	_width = 100;
	_height = 100;
}


void Flag::simulate_AI(Uint32, Assets*, Input*, Scene* scene, Game_Manager* game_manager)
{
	Game_Object* player = scene->get_game_object("Player");

	// Get location of center for portal and player
	Vector_2D flag_center = _translation + Vector_2D(_width / 2.0f, _height / 2.0f);
	Vector_2D player_center = player->translation() + Vector_2D(player->width() / 2.0f, player->height() / 2.0f);

	// Find distance to player 
	float distance_to_player = (flag_center - player_center).magnitude();

	// If in range
	if (distance_to_player < 50.0f)
	{
		game_manager->player_victory();
	}

}