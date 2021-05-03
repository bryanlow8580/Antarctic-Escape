#pragma once

#include "scene.h"

class Scene_Manager
{
public:
	Scene_Manager();

	Scene* current_scene();

	void add_scene(Scene* scene);

	void set_current_scene(std::string id);

private:
	std::map<std::string, Scene*> _scenes;
	Scene* _current_scene;
};