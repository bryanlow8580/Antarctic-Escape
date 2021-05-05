#pragma once

#include "scene_manager.h"

class Game_Manager
{
public:
	Game_Manager();

	void update(Scene_Manager* scene_manager);

	void player_victory();
	void player_lose_life();

	void start_game();
	void reset();

private:
	void spawn_life(Scene_Manager* scene_manager, int current_lives);
	void despawn_life(Scene_Manager* scene_manager, int current_lives);

	int _player_lives;
	int _previous_update_lives;
	bool _has_not_initialised_UI;

	bool _start_game;
	bool _player_victory;

	std::string _initialized_on_scene = "";
};