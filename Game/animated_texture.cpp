#include "animated_texture.h"
#include "texture.h"

Animated_Texture::Animated_Texture(std::string id, std::string path, SDL_Renderer* renderer, int frame_count, Uint32 frame_duration_milliseconds)
	: Texture(id, path, renderer)
{
	_current_frame				 = 0;
	_frame_count				 = frame_count;
	_frame_duration_milliseconds = frame_duration_milliseconds;
}

Animated_Texture::~Animated_Texture() 
{

}

void Animated_Texture::set_frame(Uint32 total_time_milliseconds) 
{
	_current_frame = (total_time_milliseconds / _frame_duration_milliseconds) % _frame_count;
}

void Animated_Texture::render(SDL_Renderer* renderer, SDL_Rect*, SDL_Rect* destination, SDL_RendererFlip flip, double angle) 
{

	// Calculate clip coordinates of texture
	int texture_w = 0;
	int texture_h = 0;

	// Calculate texture width
	const int query_texture_result = SDL_QueryTexture(data(), nullptr, nullptr, &texture_w, &texture_h);

	const int frame_width = texture_w / _frame_count;

	SDL_Rect frame_clip;
	frame_clip.w = frame_width;
	frame_clip.h = texture_h;
	frame_clip.x = _current_frame * frame_width;
	frame_clip.y = 0;

	Texture::render(renderer, &frame_clip, destination, flip, angle);

}