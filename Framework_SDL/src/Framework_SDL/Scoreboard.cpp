#include "Scoreboard.h"

Scoreboard::Scoreboard() : Scoreboard({255,255,255}, 32) {}

Scoreboard::Scoreboard(SDL_Color color, int size) {
	mColor = color;
	mSize = size;
	Score(0);
}

Scoreboard::~Scoreboard() {
	ClearBoard();
}

void Scoreboard::ClearBoard() {
	for (int i = 0; i < mScore.size(); ++i) {
		delete mScore[i];
		mScore[i] = nullptr;
	}

	mScore.clear();
}

void Scoreboard::Score(int score) {
	ClearBoard();

	if (score == 0) {
		for (int i = 0; i < 2; ++i) {
			mScore.push_back(new Texture("0", "ARCADE.ttf", mSize, mColor));
			mScore[i]->Parent(this);
			mScore[i]->Pos(Vector2(-32.0f, 0.0f));
		}
	}
	else {
		std::string str = std::to_string(score);
		int lastIndex = str.length() - 1;

		for (int i = 0; i <= lastIndex; ++i) {
			mScore.push_back(new Texture(str.substr(i, 1), "ARCADE.ttf", mSize, mColor));
			mScore[i]->Parent(this);
			mScore[i]->Pos(Vector2(-32.0f * (lastIndex - i), 0.0f));
		}
	}
}

void Scoreboard::Render() {
	for (int i = 0; i < mScore.size(); ++i) {
		mScore[i]->Render();
	}
}