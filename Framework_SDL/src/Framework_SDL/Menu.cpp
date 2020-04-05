#include "Menu.h"

Menu::Menu() {
	clicked = false;

	mTimer = Timer::Instance();

	mInputManager = InputManager::Instance();

	mGraphics = Graphics::Instance();

	mBackground = new Texture("bg.jpg");

	playButton = new Texture("play", "ARCADE.TTF", 73, { 255, 0, 0 });
	playButton->Pos(Vector2(200,200));
	exitButton = new Texture("exit", "ARCADE.TTF", 73, { 255, 0, 0 });
	exitButton->Pos(Vector2(200, 400));

	mScoreTest = new Scoreboard();

	mScoreTest->Pos(Vector2(200.0f,500.0f));
	mScoreTest->Score(0);
}

void Menu::EarlyUpdate() {
	
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_MOUSEMOTION:
			mMouseCoords.x = event.motion.x;
			mMouseCoords.y = event.motion.y;
			break;
		}
	}
	mInputManager->Update();

	//std::cout << "x: " << mInputManager->MousePos().x << " y: " << mInputManager->MousePos().y << std::endl;
	//std::cout << exitButton->mRenderRect.h << " " << exitButton->mRenderRect.h<< std::endl;
}

void Menu::Update() {
	if (mInputManager->MouseButtonDown(mInputManager->MOUSE_BUTTON::left)) {
		clicked = true;
	}
	else {
		clicked = false;
	}
	
}

void Menu::LateUpdate() {
	if (((mInputManager->MousePos().x >= exitButton->Pos().x - exitButton->mRenderRect.w / 2) && (mInputManager->MousePos().x <= exitButton->Pos().x + exitButton->mRenderRect.w / 2)) && 
		((mInputManager->MousePos().y >= exitButton->Pos().y - exitButton->mRenderRect.h / 2) && (mInputManager->MousePos().y <= exitButton->Pos().y + exitButton->mRenderRect.h / 2)) &&
		clicked) {
		mSceneState = SceneState::EXIT;
	}

	if (((mInputManager->MousePos().x >= playButton->Pos().x - playButton->mRenderRect.w / 2) && (mInputManager->MousePos().x <= playButton->Pos().x + playButton->mRenderRect.w / 2)) &&
		((mInputManager->MousePos().y >= playButton->Pos().y - playButton->mRenderRect.h / 2) && (mInputManager->MousePos().y <= playButton->Pos().y + playButton->mRenderRect.h / 2)) &&
		clicked) {
		mSceneState = SceneState::GOTO;
	}


	mInputManager->UpdatePreviousInput();
	mTimer->Update();
}

void Menu::Render() {
	mGraphics->Clear();

	mBackground->Render();
	playButton->Render();
	exitButton->Render();

	mScoreTest->Render();

	mGraphics->Render();
}

Menu::~Menu() {

	delete mBackground;
	mBackground = nullptr;

	delete exitButton;
	exitButton = nullptr;

	delete playButton;
	playButton = nullptr;

	delete mScoreTest;
	mScoreTest = nullptr;

	/*AudioManager::Release();
	mAudioManager = nullptr;

	AssetManager::Release();
	mAssetManager = nullptr;*/

	Graphics::Release();
	mGraphics = nullptr;

	InputManager::Release();
	mInputManager = nullptr;

	Timer::Release();
	mTimer = nullptr;

}