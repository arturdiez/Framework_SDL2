#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H
#include "Texture.h"
#include <vector>

class Scoreboard : public GameObject {
private:
	std::vector<Texture*> mScore;
public:

	SDL_Color mColor;
	int mSize;

	Scoreboard();
	Scoreboard(SDL_Color color, int size);
	~Scoreboard();

	void Score(int score);

	void Render();

private:
	void ClearBoard();
};

#endif
