#pragma once

#include <map>

class Input 
{
public:
	Input();
	~Input();

	enum class Button 
	{
		PAUSE,
		QUIT,

		UP,
		TURN_LEFT,
		TURN_RIGHT,

		INCREASE_SPEED,
		DECREASE_SPEED,
		SHOW_CREDITS,
		SHOW_LIBRARIES,
		DEBUG_SHOW_IDS,
		DEBUG_SHOW_POSITION,
		DEBUG_SHOW_COLLIDERS
	};

	enum class Button_State 
	{
		PRESSED,
		DOWN,
		RELEASED,
		UP
	};

	void get_input();
	bool is_button_state(Button type, Button_State state);

private:
	std::map<Button, Button_State> _button_state;
};