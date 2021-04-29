#pragma once

#include "player.h"
#include "sound.h"

Player::Player(std::string id)
	: Game_Object(id, "Texture.Player.Walking") 
{
	
	_translation	 = Vector_2D(50, 250);
	_speed			 = 0.1f;

	_collider.set_radius(_width / 5.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));

	_hp = 10;

	_state.push(State::Idle);	
}

Player::~Player() 
{

}

void Player::simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene*) 
{

	if (_hp <= 0) 
	{
		_state.push(State::Dying);
	}

	switch (_state.top()) 
	{
		case State::Idle:
			if (input->is_button_state(Input::Button::RUNNING, Input::Button_State::DOWN) && _velocity.magnitude() > 0.0f) 
			{
				push_state(State::Running, assets);
			}
			else if (_velocity.magnitude() > 0.0f) 
			{
				push_state(State::Walking, assets);
			}
			break;
		case State::Walking:
			if (_velocity.magnitude() == 0.0f) 
			{
				pop_state(assets);
			}
			else if (input->is_button_state(Input::Button::RUNNING, Input::Button_State::PRESSED)) 
			{
				push_state(State::Running, assets);
			}
			else if (input->is_button_state(Input::Button::SLIDING, Input::Button_State::PRESSED)) 
			{
				push_state(State::Sliding, assets);
			}
			break;
		case State::Running:
			if (_velocity.magnitude() == 0.0f) 
			{
				pop_state(assets);
			}
			else if (input->is_button_state(Input::Button::RUNNING, Input::Button_State::RELEASED)) 
			{
				pop_state(assets);
			}
			break;
		case State::Sliding:
			if (_velocity.magnitude() == 0.0f) 
			{
				pop_state(assets);
			}
			else if (input->is_button_state(Input::Button::SLIDING, Input::Button_State::RELEASED)) 
			{
				pop_state(assets);
			}
			break;
		case State::Dying:
			push_state(State::Dying, assets);
			break;

	}

	_velocity = Vector_2D(0, 0);

	if (input->is_button_state(Input::Button::RIGHT, Input::Button_State::DOWN)) 
	{
		_velocity += Vector_2D(1.0f, 0);
	}
	if (input->is_button_state(Input::Button::LEFT, Input::Button_State::DOWN)) 
	{
		_velocity += Vector_2D(-1.0f, 0);
	}
	if (input->is_button_state(Input::Button::UP, Input::Button_State::DOWN)) 
	{
		_velocity += Vector_2D(0, -1.0f);
	}
	if (input->is_button_state(Input::Button::DOWN, Input::Button_State::DOWN)) 
	{
		_velocity += Vector_2D(0, 1.0f);
	}

	_velocity.normalize();
	_velocity.scale(_speed);

	_total_time_milliseconds += milliseconds_to_simulate;
}

void Player::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) 
{

	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->set_frame(_total_time_milliseconds);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}

void Player::set_speed(float speed) 
{
	_speed = speed;
}

float Player::speed() 
{
	return _speed;
}

void Player::push_state(State state, Assets* assets) 
{
	
	handle_exit_state(_state.top(), assets);
	_state.push(state);
	handle_enter_state(_state.top(), assets);
}

void Player::pop_state(Assets* assets) 
{

	handle_exit_state(_state.top(), assets);
	_state.pop();
	handle_enter_state(_state.top(), assets);
}

void Player::handle_enter_state(State state, Assets* assets) 
{

	switch (state) 
	{
		case State::Idle:
			_texture_id = "Texture.Player.Idle";
			break;
		case State::Walking:
		{
			_texture_id = "Texture.Player.Walking";
			_speed = 0.15f;

			const int walking_channel = 1;
			Sound* sound = (Sound*)assets->get_asset("Sound.Player.Walking");
			Mix_PlayChannel(walking_channel, sound->data(), -1);

			break;
		}
		case State::Running:
		{
			_texture_id = "Texture.Player.Running";
			_speed = 0.3f;

			const int running_channel = 1;
			Sound* sound = (Sound*)assets->get_asset("Sound.Player.Running");
			Mix_PlayChannel(running_channel, sound->data(), -1);
			break;
		}
		case State::Sliding:
		{
			_texture_id = "Texture.Player.Sliding";
			_speed = 0.22f;

			const int sliding_channel = 1;
			Sound* sound = (Sound*)assets->get_asset("Sound.Player.Sliding");
			Mix_PlayChannel(sliding_channel, sound->data(), -1);

			break;
		}
		case State::Dying:
		{
			_texture_id = "Texture.Player.Dying";

			const int dying_channel = 1;
			Sound* sound = (Sound*)assets->get_asset("Sound.Player.Dying");
			Mix_PlayChannel(dying_channel, sound->data(), 1);

			break;
		}
	}
}

void Player::handle_exit_state(State state, Assets*) 
{

	switch (state) 
	{
		case State::Idle:
			break;
		case State::Walking:
		{
			const int walking_channel = 1;
			Mix_HaltChannel(walking_channel);
			break;
		}
		case State::Running:
		{
			const int running_channel = 1;
			Mix_HaltChannel(running_channel);

			break;
		}
		case State::Sliding:
		{
			const int sliding_channel = 1;
			Mix_HaltChannel(sliding_channel);

			break;
		}
		case State::Dying: 
		{
			const int dying_channel = 1;
			Mix_HaltChannel(dying_channel);

			break;
		}
	}
}