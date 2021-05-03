#include "scene_manager.h"

#include <iostream>

Scene_Manager::Scene_Manager()
{
	_current_scene = nullptr;
}

Scene* Scene_Manager::current_scene() 
{
	return _current_scene;
}

void Scene_Manager::add_scene(Scene* scene)
{
	if (_scenes.find(scene->id()) != _scenes.end())
	{
		std::cout << "Attempted to add a scene with an id that already exists. ID: " << scene->id() << std::endl;
	}

	_scenes[scene->id()] = scene;
}

void Scene_Manager::set_current_scene(std::string id)
{
	if (_scenes.find(id) == _scenes.end())
	{
		std::cout << "Attempted to find a scene that was not added. ID: " << id << std::endl;
		exit(1);
	}
	_current_scene = _scenes[id];
	// _current_scene = _scenes.find(id)->second;
}