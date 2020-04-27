#include "Timer.h"

Timer* Timer::sInstance = nullptr;

Timer* Timer::Instance() {
	if (sInstance == nullptr) {
		sInstance = new Timer();
	}
	return sInstance;
}

void Timer::Release() {
	delete sInstance;
	sInstance = nullptr;
}

Timer::Timer() {
	Reset();
	mElsapsedTicks = 0;
	mDeltaTime = 0.0f;
	mTimeScale = 1.0f;
}

Timer::~Timer() {

}

void Timer::Reset() {
	mStartTicks = SDL_GetTicks();
}

float Timer::DeltaTime() {
	return mDeltaTime;
}

void Timer::TimeScale(float t) {
	mTimeScale = t;

}

float Timer::TimeScale() {
	return mTimeScale;
}

void Timer::Update() {
	mElsapsedTicks = SDL_GetTicks() - mStartTicks;
	mDeltaTime = mElsapsedTicks * 0.001f;
}