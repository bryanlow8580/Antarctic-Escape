#pragma once

#define SDL_MAIN_HANDLED

#include <SDL.h>

#include "asset.h"
#include "texture.h"

// Any object using animated texture has to have private Uint32 total_time_milliseconds (basically total time alive) to call set_frame
// and update total_time_milliseconds in their AI ( += milliseconds_to_simulate )

class Animated_Texture : public Texture 
{
public: 
	Animated_Texture(std::string id, std::string path, SDL_Renderer* renderer, int frame_count, Uint32 frame_duration_milliseconds);
	~Animated_Texture();

	void set_frame(Uint32 total_time_milliseconds);
	void render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* destination, SDL_RendererFlip flip) override;

private: 
	int _frame_count;
	Uint32 _frame_duration_milliseconds;
	int	_current_frame;
};