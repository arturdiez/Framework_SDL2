#include "Graphics.h"

Graphics* Graphics::sInstance = nullptr;
bool Graphics::sInitialized = false;

Graphics* Graphics::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Graphics();
	}
	return sInstance;
}

Graphics::Graphics() {
	mBuffer = nullptr;

	sInitialized = Init();
}

Graphics::~Graphics() {
	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;

	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Graphics::Release() {
	delete sInstance;
	sInstance = nullptr;
	sInitialized = false;
}

bool Graphics::Initialized() {
	return sInitialized;
}

bool Graphics::Init() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cout << "SDL Initialization Error\n" << SDL_GetError();
		return false;
	}

	mWindow = SDL_CreateWindow("SDL_FRAMEWORK", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	
	if (mWindow == nullptr) {
		std::cout << "Window creation Error\n" << SDL_GetError();
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	
	if (mRenderer == nullptr) {
		std::cout << "Renderer creation Error\n" << SDL_GetError();
		return false;
	}

	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags)) {
		std::cout << "Image initialization Error\n" << IMG_GetError();
		return false;
	}

	if (TTF_Init() == -1) {
		std::cout << "TTF initialization Error\n" << TTF_GetError();
		return false;
	}

	mBuffer = SDL_GetWindowSurface(mWindow);

	return true;
}

SDL_Texture* Graphics::LoadTexture(std::string path) {
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr) {
		std::cout << "Image load Error\n" << IMG_GetError();
		return texture;
	}
	texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	if (texture == nullptr) {
		std::cout << "Create texture Error\n" << SDL_GetError();
		return texture;
	}
	SDL_FreeSurface(surface);
	return texture;
}

SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surface == nullptr) {
		std::cout << "Text render Error\n" << TTF_GetError();
		return nullptr;
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
	if (texture == nullptr) {
		std::cout << "Text texture Error\n" << TTF_GetError();
		return nullptr;
	}
	SDL_FreeSurface(surface);
	
	return texture;
}

void Graphics::Clear() {
	SDL_RenderClear(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture* texture, SDL_Rect* clipped, SDL_Rect* rend, float angle, SDL_RendererFlip flip) {

	SDL_RenderCopyEx(mRenderer, texture, clipped, rend, angle, NULL, flip);
}

void Graphics::Render() {
	SDL_RenderPresent(mRenderer);
}