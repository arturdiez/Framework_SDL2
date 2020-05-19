#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "GameObject.h"
#include "AssetManager.h"

class Texture: public GameObject {
protected:
	SDL_Texture* mTexture;
	Graphics* mGraphics;

	bool mClipped;
	int mWidth;
	int mHeight;
	
public:
	
	SDL_Rect mRenderRect;
	SDL_Rect mClippedRect;


public:
	Texture(std::string fileName);
	Texture(std::string fileName, int x, int y, int w, int h);
	Texture(std::string text, std::string fontPath, int size, SDL_Color color);
	~Texture();

	Vector2 ScaledDimensions();

	virtual void Render();
};

#endif 

