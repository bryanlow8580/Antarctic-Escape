#pragma once

#include "game_object.h"
#include "text.h"

#include <iostream>

Game_Object::Game_Object(std::string id, std::string texture_id)
	: _translation(0, 0), _velocity(0, 0), _collider(0.0f, Vector_2D(0.f, 0.f)) 
{

	_id			= id;
	_texture_id = texture_id;

	_width  = 100;
	_height = 100;

	_angle = 0;

	_blocked_by_wall = false;

	_flip = SDL_FLIP_NONE;
}

Game_Object::~Game_Object() 
{

}

std::string Game_Object::id() 
{
	return _id;
}

Vector_2D Game_Object::translation() 
{
	return _translation;
}

Vector_2D Game_Object::velocity() 
{
	return _velocity;
}

int Game_Object::width() 
{
	return _width;
}

int Game_Object::height() 
{
	return _height;
}

bool Game_Object::blocked_by_wall()
{
	return _blocked_by_wall;
}

void Game_Object::set_translation(Vector_2D translation) 
{
	_translation = translation;
}

void Game_Object::set_hp(int hp) 
{
	_hp = hp;
}

void Game_Object::simulate_physics(Uint32 milliseconds_to_simulate, Assets*, Scene* scene) 
{
	Vector_2D velocity = _velocity;
	velocity.scale((float)milliseconds_to_simulate);

	_translation += velocity;

	for (Game_Object* game_object : scene->get_game_objects()) 
	{

		if (game_object->id() == _id) 
		{
			continue;
		}

		Collider collider	    = Collider(_collider.width(), _collider.height(), _collider.translation() + _translation);

		Collider other_collider = Collider(game_object->_collider.width(), game_object->_collider.height(), game_object->_collider.translation() + game_object->_translation);

		Vector_2D intersection_depth	  = collider.intersection_depth(other_collider);
		float intersection_depth_magnitude = intersection_depth.magnitude();

		if (intersection_depth_magnitude > 0.0f)
		{

			other_collider.set_weight(game_object->_collider.weight());
			collider.set_weight(_collider.weight());
			const float weight_ratio = collider.weight() / (collider.weight() + other_collider.weight());

			Vector_2D other_collider_to_collider = collider.translation() - other_collider.translation();

			if (collider.weight() >= 990)
			{
				other_collider_to_collider.scale(0);
			}
			else if (weight_ratio <= 0.05)
			{
				// scaled by 1
				other_collider_to_collider.scale(1 / intersection_depth_magnitude);
			}
			else
			{
				other_collider_to_collider.scale(weight_ratio);
				other_collider_to_collider.normalize();
				other_collider_to_collider.scale(1 / intersection_depth_magnitude);
			}

			//other_collider_to_collider = Vector_2D(other_collider_to_collider.x() / intersection_depth_magnitude, other_collider_to_collider.y() / intersection_depth_magnitude);
			//other_collider_to_collider.scale(intersection_depth_magnitude);

			_translation += other_collider_to_collider;

			Vector_2D collider_to_other_collider = other_collider.translation() - collider.translation();

			if (weight_ratio <= 0.05) 
			{ 
				collider_to_other_collider.scale(0);
			} 
			else
			{
				collider_to_other_collider.scale(1 / weight_ratio);
				collider_to_other_collider.normalize();
				other_collider_to_collider.scale(1 / intersection_depth_magnitude);
			}
			std::cout << "Weight Ratio : " << weight_ratio << "\nThis Pushback: " << other_collider_to_collider.x() << " " << other_collider_to_collider.y() << std::endl
				<< "That pushback: " << collider_to_other_collider.x() << " " << collider_to_other_collider.y() << std::endl
				<< "Intersection depth: " << intersection_depth.x() << " " << intersection_depth.y() << std::endl;

			//collider_to_other_collider = Vector_2D(collider_to_other_collider.x() / intersection_depth_magnitude, collider_to_other_collider.y() / intersection_depth_magnitude);
			//collider_to_other_collider.scale(intersection_depth_magnitude);

			game_object->_translation += collider_to_other_collider;
		}

		//Circle_2D collider		 = Circle_2D(_collider.radius(), _collider.translation() + _translation);
		//Circle_2D other_collider = Circle_2D(game_object->_collider.radius(), game_object->_collider.translation() + game_object->_translation);
		//float intersection_depth = collider.intersection_depth(other_collider);

		//if (intersection_depth > 0.0f) 
		//{

		//	// pushes objects away from each other if intersecting / colliding
		//	Vector_2D other_collider_to_collider = collider.translation() - other_collider.translation();
		//	other_collider_to_collider.normalize();
		//	other_collider_to_collider.scale(intersection_depth);
		//	_translation += other_collider_to_collider;

		//	Vector_2D collider_to_other_collider = other_collider.translation() - collider.translation();
		//	collider_to_other_collider.normalize();
		//	collider_to_other_collider.scale(intersection_depth);
		//	game_object->_translation += collider_to_other_collider;
		//}

	}
}

void Game_Object::render(Uint32, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) 
{
	SDL_Rect destination;

	destination.x = (int)(_translation.x() - scene->camera_translation().x());
	destination.y = (int)(_translation.y() - scene->camera_translation().y());
	destination.w = _width;
	destination.h = _height;

	/*const float PI = 3.14159265f;
	if (_velocity.magnitude() > 0) 
	{
		if (abs(_velocity.angle()) <= (PI / 2.f)) 
		{
			_flip = SDL_FLIP_NONE;
		}
		else 
		{
			_flip = SDL_FLIP_HORIZONTAL;
		}
	}*/

	Texture* texture = (Texture*)assets->get_asset(_texture_id);
	texture->render(renderer, nullptr, &destination, SDL_FLIP_NONE, _angle);

	if (config->should_display_ids) 
	{
		SDL_Color text_color;
		text_color.r = 255;
		text_color.g = 255;
		text_color.b = 0;
		text_color.a = 255;

		Text id(renderer, _id.c_str(), text_color, "ID.Text");
	
		id.render(renderer, _translation + Vector_2D((float)_width / 2, (float)_height) - scene->camera_translation());
	}
	if (config->should_display_position) 
	{
		SDL_Color text_color;
		text_color.r = 255;
		text_color.g = 255;
		text_color.b = 0;
		text_color.a = 255;

		std::string position = std::to_string(_translation.x()) + ", "+ std::to_string(_translation.y());
		std::string angle = std::to_string(_angle);

		Text id(renderer, position.c_str(), text_color, "ID.Text");

		id.render(renderer, _translation + Vector_2D((float)_width / 2, (float)_height + 15) - scene->camera_translation());

		Text angle_text(renderer, angle.c_str(), text_color, "Angle.Text");
		angle_text.render(renderer, _translation + Vector_2D((float)_width / 2, (float)_height - 15) - scene->camera_translation());
	}

	if (config->should_display_colliders && _collider.radius() > 0.f) 
	{
		Texture* collider_texture = (Texture*)assets->get_asset("Texture.Collider");

		SDL_Rect collider_destination;
		collider_destination.x = (int)(_translation.x() + _collider.translation().x() - _collider.radius() - scene->camera_translation().x());
		collider_destination.y = (int)(_translation.y() + _collider.translation().y() - _collider.radius() - scene->camera_translation().y());
		collider_destination.w = (int)(_collider.radius() * 2.0f);
		collider_destination.h = (int)(_collider.radius() * 2.0f);

		collider_texture->render(renderer, nullptr, &collider_destination, SDL_FLIP_NONE, _angle);
	}
}
