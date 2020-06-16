#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include <fmod_studio.hpp>
#include <fmod.hpp>

using namespace std;

class Audio
{
public:
	Audio();
	Audio(const char* filename);
	~Audio();
	void Play();
	void ChangeSoundLevel(float soundLevel);
	FMOD::Studio::System* system = NULL;
private:
	FMOD::System* lowLevelSystem = NULL;
	FMOD::Sound* sound = NULL;
	FMOD::Channel* soundChannel = NULL;
};

