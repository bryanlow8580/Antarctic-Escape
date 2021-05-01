#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <string>
#include <iostream>
#include <SDL_image.h>

#include "texture.h"

Texture::Texture(std::string id, std::string path, SDL_Renderer* renderer) : Asset(id)
{

	// Create SDL Surface
	SDL_Surface* surface;

	if (path.find("bmp") != std::string::npos) 
	{
		// Load BMP image
		// Allows string path to be read as char*
		surface = SDL_LoadBMP(path.c_str());
	}
	else if (path.find("png") != std::string::npos) 
	{
		// Load PNG file
		surface = IMG_Load(path.c_str());
	}
	else 
	{
		std::cout << "Unknown image file extension. Path: " << path << std::endl;
		exit(1);
	}

	if (surface == nullptr) 
	{
		std::cout << "Failed to load image. Path: " << path << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	// Create SDL Texture from SDL Surface and cache it in _data
	_data = SDL_CreateTextureFromSurface(renderer, surface);

	// Free Surface
	SDL_FreeSurface(surface);

}

Texture::~Texture() 
{
	// Free _data
	SDL_DestroyTexture(_data);
}

SDL_Texture* Texture::data() 
{
	return _data;
}

void Texture::render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* destination, SDL_RendererFlip flip, double angle) 
{

	int render_result, render_success = 0;
	SDL_Point* center = nullptr;

	render_result = SDL_RenderCopyEx(renderer, _data, clip, destination, angle, center, flip);

	if (render_result != render_success) 
	{
		std::cout << "Failed to render texture" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

}