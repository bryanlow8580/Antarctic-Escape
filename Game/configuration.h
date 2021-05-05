#pragma once

struct Configuration 
{
	bool should_display_ids = false;
	bool should_display_position = false;
	bool should_display_colliders = false;
	bool pause = false;

	int window_width  = 1366;
	int window_height = 800;
};