#ifndef _AUDIOMANAGER_H
#define _AUDIOMANAGER_H
#include "AssetManager.h"

class AudioManager {
private:
	static AudioManager* sInstance;
	AssetManager* mAssetManager;
public:
	//singleton Creation & Releasing
	static AudioManager* Instance();
	static void Release();

	//Play, Pause, Resume Music
	void PlayMusic(std::string fileName, int loop = 1);
	void PauseMusic();
	void ResumeMusic();

	//Play SFX
	void PlaySoundFX(std::string fileName, int loop = 0, int channel = 0);
private:
	//Constructor & Destructor
	AudioManager();
	~AudioManager();

};

#endif 

