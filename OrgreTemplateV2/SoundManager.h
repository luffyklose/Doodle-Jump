#pragma once
#define SDL_MAIN_HANDLED
#include <SDL_mixer.h>

enum sound_type
{
	SOUND_MUSIC = 0,
	SOUND_SFX = 1
};

class SoundManager
{
public:
	/// <summary>
	/// default constructor
	/// </summary>
	SoundManager();

	/// <summary>
	/// default destructor
	/// </summary>
	~SoundManager();

	/// <summary>
	/// load sound source files
	/// </summary>
	/// <param name="FileName"></param>
	/// <param name="type"></param>
	/// <returns></returns>
	bool Load(const char* FileName, sound_type type);

	/// <summary>
	/// initialize
	/// </summary>
	void InitAll();

	/// <summary>
	/// play music
	/// </summary>
	/// <param name="FileName"></param>
	/// <param name="loop"></param>
	void PlayMusic(const char* FileName, int loop);

	/// <summary>
	/// play sound
	/// </summary>
	/// <param name="FileName"></param>
	/// <param name="loop"></param>
	void PlaySound(const char* FileName, int loop);

	/// <summary>
	/// get instance for singleton
	/// </summary>
	/// <returns></returns>
	static SoundManager* Instance();

private:
	/// <summary>
	/// int value for current sound volume
	/// </summary>
	int CurrentVolume = MIX_MAX_VOLUME / 2;

	/// <summary>
	/// current music to play
	/// </summary>
	Mix_Music* pMusic = nullptr;

	/// <summary>
	/// current sound to play
 	/// </summary>
	Mix_Chunk* pSound = nullptr;

	/// <summary>
	/// SoundManager instance for singleton
	/// </summary>
	static SoundManager* s_pInstance;
};
