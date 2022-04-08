#include "SoundManager.h"
#include <iostream>

SoundManager* SoundManager::s_pInstance = NULL;

SoundManager* SoundManager::Instance()
{
	if (s_pInstance == 0)
	{
		s_pInstance = new SoundManager();
	}

	return s_pInstance;
}

SoundManager::SoundManager()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize!" << std::endl;
	}
}

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}

bool SoundManager::Load(const char* FileName, sound_type type)
{
	if (type == SOUND_MUSIC)
	{
		pMusic = Mix_LoadMUS(FileName);

		if (pMusic == 0)
		{
			std::cout << "Music Load Failed!" << std::endl;
			return false;
		}

		return true;
	}
	else if (type == SOUND_SFX)
	{
		pSound = Mix_LoadWAV(FileName);
		if (pSound == 0)
		{
			std::cout << "Sound:" << FileName << " Load Failed!" << std::endl;
			return false;
		}
		return true;
	}

	return false;
}

void SoundManager::InitAll()
{
	if (!Load("Assests/Audio/Battle_BGM.wav", SOUND_MUSIC))
	{
		std::cout << "MUSIC LOAD FAILED" << std::endl;
	}

	if (!Load("Assests/Audio/Ding.wav", SOUND_SFX))
	{
		std::cout << "DING SFX LOAD FAILED" << std::endl;
	}
}

void SoundManager::PlayMusic(const char* FileName, int loop)
{
	pMusic = Mix_LoadMUS(FileName);
	Mix_PlayMusic(pMusic, loop);
}

void SoundManager::PlaySound(const char* FileName, int loop)
{
	pSound = Mix_LoadWAV(FileName);
	Mix_PlayChannel(-1, pSound, loop);
}