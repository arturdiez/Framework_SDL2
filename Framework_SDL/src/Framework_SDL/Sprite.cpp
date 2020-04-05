#include "Sprite.h"

Sprite::Sprite(std::string fileName, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir)
	: Texture(fileName, x, y, w, h) {
	mTimer = Timer::Instance();

	mStartX = x;
	mStartY = y;

	mFrameCount = frameCount;
	mAnimSpeed = animationSpeed;
	mTimePerFrame = mAnimSpeed / mFrameCount;
	mAnimTimer = 0.0f;

	mAnimDir = animationDir;

	mAnimDone = false;

	mWrapMode = loop;
}

Sprite::~Sprite() {

}

void Sprite::WrapMode(WRAP_MODE wrapMode) {
	mWrapMode = wrapMode;
}

void Sprite::ResetAniamtion() {
	mAnimTimer = 0.0f;
	mAnimDone = false;
}

bool Sprite::IsAnimating() {
	return !mAnimDone;
}

void Sprite::Update() {
	if (!mAnimDone) {
		mAnimTimer += mTimer->DeltaTime();
		if (mAnimTimer >= mAnimSpeed) {
			if (mWrapMode == loop) {
				mAnimTimer -= mAnimSpeed;
			}
			else {
				mAnimDone = true;
				mAnimTimer = mAnimSpeed - mTimePerFrame;
			}
		}
		if (mAnimDir == horizontal) {
			mClippedRect.x = mStartX + (int)(mAnimTimer / mTimePerFrame) * mWidth;
		}
		else {
			mClippedRect.y = mStartY + (int)(mAnimTimer / mTimePerFrame) * mHeight;
		}
	}
}