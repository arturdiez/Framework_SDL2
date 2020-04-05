#include "AssetManager.h"

AssetManager* AssetManager::sInstance = nullptr;

//Creation Of singleton and its Releasing
AssetManager* AssetManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new AssetManager();
	}
	return sInstance;
}
void AssetManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

//Construcotr & Destructor
AssetManager::AssetManager() {
}
AssetManager::~AssetManager() {
	for (auto texture : mTextures) {
		if (texture.second != nullptr) {
			SDL_DestroyTexture(texture.second);
		}
	}
	mTextures.clear();

	for (auto texts : mTexts) {
		if (texts.second != nullptr) {
			SDL_DestroyTexture(texts.second);
		}
	}
	mTexts.clear();

	for (auto fonts : mFonts) {
		if (fonts.second != nullptr) {
			TTF_CloseFont(fonts.second);
		}
	}
	mFonts.clear();

	for (auto music : mMusic) {
		if (music.second != nullptr) {
			Mix_FreeMusic(music.second);
		}
	}
	mMusic.clear();

	for (auto sfx : mSoundFX) {
		if (sfx.second != nullptr) {
			Mix_FreeChunk(sfx.second);
		}
	}
	mSoundFX.clear();

}


//Getters That return same memory pointer if we want the same file if it was previously loaded
SDL_Texture* AssetManager::GetTexture(std::string fileName) {
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/img/" + fileName);

	if (mTextures[fullPath] == nullptr) {
		mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);
	}
	return mTextures[fullPath];
}
TTF_Font* AssetManager::GetFont(std::string fileName, int size) {
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/ttf/" + fileName);
	std::string key = fullPath + (char)size;

	if (mFonts[key] == nullptr) {
		mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);
		if (mFonts[key] == nullptr) {
			std::cout << "Font loading Error" << TTF_GetError();
		}
	}
	return mFonts[key];
}
SDL_Texture* AssetManager::GetText(std::string text, std::string fileName, int size, SDL_Color color) {
	TTF_Font* font = GetFont(fileName, size);

	std::string key = text + fileName + (char)size + (char)color.r + (char)color.b + (char)color.g;
	if (mTexts[key] == nullptr) {
		mTexts[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
	}
	return mTexts[key];
}
Mix_Music* AssetManager::GetMusic(std::string fileName) {
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/au/" + fileName);
	if (mMusic[fullPath] == nullptr) {
		mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());
		if (mMusic[fullPath] == nullptr) {
			std::cout << "Music loading Error\n" << Mix_GetError();
		}
	}
	return mMusic[fullPath];
}
Mix_Chunk* AssetManager::GetSoundFX(std::string fileName) {
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/au/" + fileName);

	if (mSoundFX[fullPath] == nullptr) {
		mSoundFX[fullPath] = Mix_LoadWAV(fullPath.c_str());
		if (mSoundFX[fullPath] == nullptr) {
			std::cout << "Sound FX loading Error\n" << Mix_GetError();
		}
	}
	return mSoundFX[fullPath];
}