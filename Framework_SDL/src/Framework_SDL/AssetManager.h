#ifndef _ASSETMANAGER_H
#define _ASSETMANAGER_H
#include "Graphics.h"
#include "SDL_mixer.h"
#include <map>

class AssetManager {
private:
	static AssetManager* sInstance;
	std::map<std::string, SDL_Texture*>mTextures;
	std::map<std::string, SDL_Texture*>mTexts;
	std::map<std::string, TTF_Font*>mFonts;
	std::map<std::string, Mix_Music*> mMusic;
	std::map<std::string, Mix_Chunk*>mSoundFX;
public:
	static AssetManager* Instance();
	static void Release();

	//Getters Texture, Text, Music, SoundFX
	SDL_Texture* GetTexture(std::string fileName);
	SDL_Texture* GetText(std::string text, std::string fileName, int size, SDL_Color color);
	Mix_Music* GetMusic(std::string fileName);
	Mix_Chunk* GetSoundFX(std::string fileName);

private:
	//Constructor & Destructor
	AssetManager();
	~AssetManager();

	//Getter Font
	TTF_Font* GetFont(std::string fileName, int size);
};

#endif 

