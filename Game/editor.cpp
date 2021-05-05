#pragma once

#include "editor.h"
#include "resource.h"
#include "player.h"
#include "assets.h"

#include <SDL.h>
#include <SDL_syswm.h>
#include <iostream>

Editor::Editor(std::wstring window_name)
{
	
	// Finds window based on a string
	_window = FindWindow(NULL, window_name.c_str());

	if (_window == NULL) 
	{
		std::cout << "Failed to find window. Window Name: " << window_name.c_str() << std::endl;
		exit(1);
	}

	// Load menu using an ID, default ID is IDR_MENU1 for the first menu
	_menu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));
	
	if (_menu == NULL) 
	{
		std::cout << "Failed to create menu." << std::endl;
		exit(1);
	}

	BOOL set_menu_result = SetMenu(_window, _menu);

	if (set_menu_result == 0) 
	{
		std::cout << "Failed to set menu." << std::endl;
		exit(1);
	}

	// Allows handling of events from windows, e.g. the menus
	Uint8 event_state_result = SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
	Uint8 event_state_success = SDL_DISABLE;

	if (event_state_result != event_state_success) 
	{
		std::cout << "Failed to enable Windows event state." << std::endl;
		exit(1);
	}
}

Editor::~Editor() 
{

}

INT_PTR CALLBACK Dialog_Proc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM) 
{

	switch (Message) 
	{
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam)) 
			{
				case IDC_BUTTON1:
					EndDialog(hwnd, IDOK);
					break;
			}
		default:
			return FALSE;
	}
}

void Editor::update(Input* input, Scene*, Configuration* config) 
{

	if (input->is_button_state(Input::Button::PAUSE, Input::Button_State::PRESSED)) 
	{
		config->pause = !config->pause;
	}
	if (input->is_button_state(Input::Button::SHOW_CREDITS, Input::Button_State::PRESSED)) 
	{
		DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG1), _window, Dialog_Proc);
	}
	if (input->is_button_state(Input::Button::DEBUG_SHOW_IDS, Input::Button_State::PRESSED)) 
	{
		config->should_display_ids = !config->should_display_ids;
	}
	if (input->is_button_state(Input::Button::DEBUG_SHOW_POSITION, Input::Button_State::PRESSED)) 
	{
		config->should_display_position = !config->should_display_position;
	}

	if (input->is_button_state(Input::Button::DEBUG_SHOW_COLLIDERS, Input::Button_State::PRESSED)) 
	{
		config->should_display_colliders = !config->should_display_colliders;
	}
	if (input->is_button_state(Input::Button::SHOW_LIBRARIES, Input::Button_State::PRESSED)) 
	{
		DialogBox(GetModuleHandle(0), MAKEINTRESOURCE(IDD_DIALOG2), _window, Dialog_Proc);
	}
}