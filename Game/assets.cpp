#include <iostream>
#include "assets.h"
#include "texture.h"
#include "animated_texture.h"
#include "sound.h"
#include <SDL_mixer.h>

Assets::Assets(SDL_Renderer* renderer)
{
	// Cache Player Walking Texture
	{
		const int frame_count					 = 3;
		const Uint32 frame_duration_milliseconds = 200;

		Animated_Texture* texture = new Animated_Texture("Texture.Player.Walking", "Assets/penguin.walk.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[texture->id()] = texture;
	}
	
	// Create player running texture.
	{
		const int frame_count					 = 3;
		const Uint32 frame_duration_milliseconds = 100;

		Asset* texture = new Animated_Texture("Texture.Player.Running", "Assets/penguin.walk.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[texture->id()] = texture;
	}

	// Create player idle texture.
	{
		const int frame_count					 = 3;
		const Uint32 frame_duration_milliseconds = 200;

		Asset* texture = new Animated_Texture("Texture.Player.Idle", "Assets/penguin.idle.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[texture->id()] = texture;
	}

	// Create player sliding texture.
	{
		const int frame_count					 = 3;
		const Uint32 frame_duration_milliseconds = 200;

		Asset* texture = new Animated_Texture("Texture.Player.Sliding", "Assets/penguin.slide.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[texture->id()] = texture;
	}

	// Create player dying texture.
	{
		const int frame_count					 = 3;
		const Uint32 frame_duration_milliseconds = 200;

		Asset* texture = new Animated_Texture("Texture.Player.Dying", "Assets/penguin.die.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[texture->id()] = texture;
	}

	// Enemy walking texture
	{
		const int frame_count					 = 3;
		const Uint32 frame_duration_milliseconds = 200;

		Asset* texture = new Animated_Texture("Texture.Enemy.Walking", "Assets/enemy.walking.png", renderer, frame_count, frame_duration_milliseconds);
		_assets[texture->id()] = texture;
	}

	// Collider Texture 
	{
		Texture* texture = new Texture("Texture.Collider", "Assets/collider.png", renderer);
		_assets[texture->id()] = texture;
	}

	// Ice Texture
	{
		Texture* texture = new Texture("Texture.Ice", "Assets/ice.png", renderer);
		_assets[texture->id()] = texture;
	}
	
	// Wall Texture
	{
		Texture* texture = new Texture("Texture.Wall", "Assets/wall.png", renderer);
		_assets[texture->id()] = texture;
	}

	// Heart Texture
	{
		Texture* texture = new Texture("Texture.Life", "Assets/heart.png", renderer);
		_assets[texture->id()] = texture;
	}
	
	// Flag Texture
	{
		Texture* texture = new Texture("Texture.Flag", "Assets/flag.png", renderer);
		_assets[texture->id()] = texture;
	}

	// Game Title Texture
	{
		Texture* texture = new Texture("Texture.Game.Title", "Assets/game.title.png", renderer);
		_assets[texture->id()] = texture;
	}

	// Continue Texture 
	{
		Texture* texture = new Texture("Texture.Game.Continue", "Assets/game.continue.png", renderer);
		_assets[texture->id()] = texture;
	}

	// Game Over Texture
	{
		Texture* texture = new Texture("Texture.Game.Over", "Assets/game.over.png", renderer);
		_assets[texture->id()] = texture;
	}

	// Game Victory Texture
	{
		Texture* texture = new Texture("Texture.Game.Victory", "Assets/game.victory.png", renderer);
		_assets[texture->id()] = texture;
	}


	///Sounds
	// Background Music Asset
	{
		Sound* sound		 = new Sound("Sound.Music", "Assets/bgm.wav");
		_assets[sound->id()] = sound;

		Mix_PlayChannel(0, sound->data(), -1);
	}

	// Player Walking Sound
	{
		Sound* sound	     = new Sound("Sound.Player.Walking", "Assets/walking.wav");
		_assets[sound->id()] = sound;
	}

	// Player Running Sound
	{
		Sound* sound		 = new Sound("Sound.Player.Running", "Assets/running.wav");
		_assets[sound->id()] = sound;
	}

	// Player Sliding Sound
	{
		Sound* sound		 = new Sound("Sound.Player.Sliding", "Assets/sliding.ogg");
		_assets[sound->id()] = sound;
	}

	// Player Dying Sound
	{
		Sound* sound		 = new Sound("Sound.Player.Dying", "Assets/death.wav");
		_assets[sound->id()] = sound;
	}
}

Assets::~Assets() 
{

}

Asset* Assets::get_asset(std::string id) 
{
	if (_assets.find(id) == _assets.end()) 
	{

		std::cout << "Attempted to find an asset that was not loaded. ID: " << id << std::endl;
		exit(1);
	}
	
	return _assets[id];
}