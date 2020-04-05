#ifndef _SPRITE_H
#define _SPRITE_H
#include"Timer.h"
#include "Texture.h"

class Sprite: public Texture {
public:
	enum WRAP_MODE {once = 0, loop = 1};
	enum ANIM_DIR {horizontal = 0, vertical = 1};
private:
	Timer* mTimer;

	//Position of the frame
	int mStartX;
	int mStartY;

	float mAnimTimer;
	float mAnimSpeed;
	float mTimePerFrame;

	int mFrameCount;

	WRAP_MODE mWrapMode;
	ANIM_DIR mAnimDir;

	bool mAnimDone;
public:
	Sprite(std::string fileName, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir);
	~Sprite();

	void WrapMode(WRAP_MODE wrapMode);

	void ResetAniamtion();

	bool IsAnimating();

	void Update();
};


#endif
