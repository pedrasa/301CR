#include "Audio.h"

Audio::Audio()
{
}

Audio::Audio(const char* filename)
{
	FMOD::Studio::System::create(&system);//create system for sound

	if (system) {
		cout << "High-level (fmod studio) audio system created." << "\n";
	}

	system->getLowLevelSystem(&lowLevelSystem);

	if (lowLevelSystem) {
		cout << "Low-level (fmod) audio system created." << "\n";
	}

	lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_STEREO, 0);
	system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, NULL);


	lowLevelSystem->createSound(filename, FMOD_LOOP_OFF, NULL, &sound);

	if (sound) {
		cout << "Sound loaded." << "\n";
	}

	sound->setDefaults(16400, 0);

	//system->update();//call this on update function of the event call
}

Audio::~Audio()
{
}

void Audio::Play()
{
	lowLevelSystem->playSound(sound, NULL, false, &soundChannel);
}

void Audio::ChangeSoundLevel(float soundLevel)
{
	soundChannel->setVolume(soundLevel);
}
