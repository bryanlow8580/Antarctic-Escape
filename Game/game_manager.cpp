#include "game_manager.h"
#include "game_scene.h"
#include "life.h"

Game_Manager::Game_Manager()
{
	_player_lives		   = 3;
	_previous_update_lives = _player_lives;
	
	_initialized_on_scene  = "";

	_has_not_initialised_UI = true;
	_player_victory = false;
}

void Game_Manager::update(Scene_Manager* scene_manager)
{
	Scene* current_scene = scene_manager->current_scene();

	if (_has_not_initialised_UI)
	{
		for (int life_index = 1; life_index <= _player_lives; life_index++)
		{
			spawn_life(scene_manager, life_index);
		}

		_initialized_on_scene = current_scene->id();
	}

	_has_not_initialised_UI = _initialized_on_scene.length() == 0
		|| _initialized_on_scene != current_scene->id();	// checks if scene is changed

	if (_previous_update_lives < _player_lives)
	{
		spawn_life(scene_manager, _previous_update_lives);
	}
	else if (_previous_update_lives > _player_lives)
	{
		despawn_life(scene_manager, _previous_update_lives);
	}
	_previous_update_lives = _player_lives;

	if (_player_lives <= 0)
	{
		scene_manager->set_current_scene("Game_Over");
	}
	if (_player_victory)
	{
		scene_manager->set_current_scene("Victory");
	}
}

void Game_Manager::player_victory()
{
	_player_victory = true;
}

void Game_Manager::player_lose_life()
{
	_player_lives --;
}

void Game_Manager::spawn_life(Scene_Manager* scene_manager, int current_lives)
{
	Life* life = new Life(std::string("Life_") + std::to_string(current_lives), Vector_2D(current_lives * 30.f - 30.f, 0.f));

	scene_manager->current_scene()->add_game_object(life);
}

void Game_Manager::despawn_life(Scene_Manager* scene_manager, int current_lives)
{
	std::string life_id = std::string("Life_") + std::to_string(current_lives);

	scene_manager->current_scene()->remove_game_object(life_id);

	_has_not_initialised_UI = true;
}