#pragma once

#include "dino.h"

Dino::Dino(std::string id)
	: Game_Object(id, "Texture.Dino") 
{

	_translation = Vector_2D(50, 350);

	_collider.set_radius(_width / 5.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height / 2.0f));
	_collider.set_weight(999);
}

Dino::~Dino() 
{

}

void Dino::simulate_AI(Uint32, Assets*, Input*, Scene*, Game_Manager*) 
{

}