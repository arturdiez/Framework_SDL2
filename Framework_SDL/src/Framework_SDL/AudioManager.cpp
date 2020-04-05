#include"AudioManager.h"

AudioManager* AudioManager::sInstance = nullptr;

//Creation & Releasing singleton
AudioManager* AudioManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new AudioManager();
	}
	return sInstance;
}
void AudioManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

//Constructor & Destructor
AudioManager::AudioManager() {
	mAssetManager = AssetManager::Instance();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
		std::cout << "Mixer initialization Error\n" << Mix_GetError();
	}
}
AudioManager::~AudioManager() {
	mAssetManager = nullptr;
	Mix_Quit();
}

//Play, Pause, Resume Music
void AudioManager::PlayMusic(std::string fileName, int loop) {
	Mix_PlayMusic(mAssetManager->GetMusic(fileName), loop);
}
void AudioManager::PauseMusic() {
	if (Mix_PlayingMusic != 0) {
		Mix_PauseMusic();
	}
}
void AudioManager::ResumeMusic() {
	if (Mix_PausedMusic() != 0) {
		Mix_ResumeMusic();
	}
}

//Play SFX
void AudioManager::PlaySoundFX(std::string fileName, int loop, int channel) {
	Mix_PlayChannel(channel, mAssetManager->GetSoundFX(fileName), loop);
}