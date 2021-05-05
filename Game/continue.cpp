#include "continue.h"

Continue::Continue(std::string id, Vector_2D translation)
	: Game_Object(id, "Texture.Game.Continue")
{
	_translation = translation;

	_width = 300;
	_height = 200;
}

void Continue::simulate_AI(Uint32, Assets*, Input* input, Scene*, Game_Manager* game_manager)
{
	if (input->is_button_state(Input::Button::START, Input::Button_State::PRESSED))
	{
		game_manager->start_game();
	}
}