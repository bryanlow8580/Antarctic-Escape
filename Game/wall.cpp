#include "wall.h"
#include "player.h"
#include <iostream>
#include <cmath>

Wall::Wall(std::string id, Vector_2D translation, int width, int height)
	: Game_Object(id, "Texture.Wall")
{
	_width		 = width;
	_height		 = height;
	_translation = translation;
}

Wall::~Wall()
{

}

void Wall::simulate_AI(Uint32 , Assets* , Input* , Scene* scene, Game_Manager* )
{
	//Player* player = (Player*)scene->get_game_object("Player");

	for (Game_Object* game_object : scene->get_game_objects())
	{

		if (game_object->id() == _id || game_object->blocked_by_wall() == false || game_object->velocity().magnitude() <= 0)
		{
			continue;
		}

		float other_x = game_object->translation().x();
		float other_y = game_object->translation().y();

		float offset_x = (float)(game_object->width() / 2);
		float offset_y = (float)(game_object->height() / 2);


		if (other_x >= _translation.x() - offset_x && other_x <= _translation.x() + _width - offset_x
			&& other_y >= _translation.y() - offset_y && other_y <= _translation.y() + _height - offset_y)
		{

			float x_distance_to_left_border  = std::abs(_translation.x() - other_x - offset_x);
			float x_distance_to_right_border = std::abs(_translation.x() + _width - other_x - offset_x);

			float y_distance_to_top_border    = std::abs(_translation.y() - other_y - offset_y);
			float y_distance_to_bottom_border = std::abs(_translation.y() + _height - other_y - offset_y);

			// Finds the minimum distance to the border
			float minimum_distance = fmin(fmin(x_distance_to_left_border, x_distance_to_right_border), fmin(y_distance_to_top_border, y_distance_to_bottom_border));

			if (round(minimum_distance) == round(x_distance_to_left_border))
			{
				// set translation to left border
				game_object->set_translation(Vector_2D(_translation.x() - offset_x , other_y));
			}
			else if (round(minimum_distance) == round(x_distance_to_right_border))
			{
				// set translation to right border
				game_object->set_translation(Vector_2D(_translation.x() + _width - offset_x, other_y));
			}
			else if (round(minimum_distance) == round(y_distance_to_top_border))
			{
				// set translation to top border
				game_object->set_translation(Vector_2D(other_x, _translation.y() - offset_y));
			}
			else if (round(minimum_distance) == round(y_distance_to_bottom_border))
			{
				// set translation to bottom border
				game_object->set_translation(Vector_2D(other_x, _translation.y() + _height - offset_y));
			}
		}
	}

}